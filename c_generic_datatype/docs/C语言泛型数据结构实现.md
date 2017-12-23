# C语言泛型数据结构实现

> wvv 2017/12/23

### 前言

在C语言中，由于没有默认泛型支持，所以在实现数据结构的时候通常会和具体承载内容挂钩。举例如下：

按常规数据结构书上教导，如果需要设计一个栈，那么栈内容类型是确定的，即使可以通过 **typedef**的技巧使得栈可以在不同场合装入不同内容，但是在同一工程下栈无法装载不同的数据类型，这样使得如果有几个不同数据类型的栈，就需要把栈代码再实现多份，这样非常不利于代码维护。

在C语言中，何如高效复用基础数据结构便需要很多技巧，网上这方面教程非常少，本文起到一个补充作用。

本文提供两种技巧供大家参考。

### void* （空指针）方法

该技巧利用C语言中空指针无数据类型，可以进行强制转换的特点来实现。

以结构体数组循环队列为例，声明如下：

```c
typedef struct {
	int head;
	int tail;
	int count;
	int struct_sz;
	void* array[BUF_SZ]; //pointer of data type
}CircleQueue;
```

我们在array中存储需要载入的数据结构体指针，在初始化时，我们需要传入后期结构体所占内存数，用于动态内存分配。

因为我们要实现通用抽象数据结构，而数据单元是由使用者确定的，所以内存占用各不相同，所以传入数据单元长度是必不可少的参数。

这样相当于我们抽象数据类型中存放的都是实际元素的指针。原理清楚了，实现起来就是常规思路了。

以循环队列为例，常规的声明文件应该如下：

```c
CircleQueue *queue_create(int struct_sz); //size of data type
void queue_free(CircleQueue *q);
int queue_push(CircleQueue *q, void *element);
int queue_pop(CircleQueue *q, void *element);
void *queue_peek(CircleQueue *q, int index);
```

参考调用方式如下：

```c
typedef struct {
	int a;
	void(*action)(char* param);
}S1;
typedef struct {
	int a;
	char b[15];
}S2;
void f(char *s)
{
	printf(s);
}
void test_cq(void)
{
	static CircleQueue *q1, *q2;
	S1 a = { 1,f };
	S2 b = { 1,"hhggggggh" };
	q1 = queue_create(sizeof(S1));
	q2 = queue_create(sizeof(S2));
	queue_push(q1, (void*)&a);
	queue_push(q2, (void*)&b);
}
```

注意的是结构体指针转成void* 指针需要进行强制转换。

### 手动内存映射法

采用空指针法也存在一些弊端，例如：

1. 因为每个元素是动态分配的，使得元素间实际内存地址可能不连续，不便于优化。
2. 删除增加元素要动态分配内存，在嵌入式设备上，频繁动态分配很影响性能。

在内存资源少的嵌入式设备上，最好手动的规划好内存的分配，所以相对在数组中存储数据指针，不如直接将数据内容直接存放在一起。

将数据连续存放在一起后，也存在一个问题，如何删除元素和增加元素？采用空指针的时候，可以将指针悬空来删除，但是手动管理数据后如何删除呢？

解决办法是，我们可以将数据有效性问题丢给使用者来确定，由用户自定义函数来确定数据有效性，在初始化的时候利用函数指针进行用户自定义函数动态绑定。

以结构体列表为例：

声明如下：

```c
#pragma pack(1)
struct List{
	u8 item_size;
	u8 count;
	bool(*item_valid)(void *item);
	void(*item_delete)(void *item);
	u8* data; //pointer of data type
};
#pragma pack() 
struct List *list_create(int item_size, void(*item_delete)(void *),bool (*item_valid)(void*));
bool list_add(struct List *l, void *item);
bool list_del(struct List *l, u8 index);
void *list_get(struct List *l, u8 index);
```

嵌入式中，内存最好做到字节必争，一般采用平台无关 u8 之类自定义基本数据类型。

其中初始化时传入的函数指针**item_delete** 来使指定数据失效，**item_valid**来确定数据是否失效。这样就能实现数据的完全抽象。

具体实现参考如下：

``` c
static inline void* get_item_addr(struct List *l, u8 index)
{
	return l->data + index*l->item_size;
}
struct List *list_create(int item_size,void (*item_delete)(void *), bool(*item_valid)(void *))
{
	u8 i;
	struct List *list = malloc(sizeof(struct List));
	list->data = malloc(MAX_LIST_COUNT * item_size);
	list->count = 0;
	list->item_delete = item_delete;
	list->item_valid = item_valid;
	list->item_size = item_size;
	for (i = 0;i < MAX_LIST_COUNT;i++)
	{
		item_delete(get_item_addr(list, i));
	}
	return list;
}

bool list_add(struct List *l, void *item)
{
	u8 i;
	for (i = 0;i < MAX_LIST_COUNT;i++)
	{
		if (!l->item_valid(get_item_addr(l,i)))
		{
			memcpy((void*)get_item_addr(l,i),item, l->item_size);
			return TRUE;
		}
	}
	return FALSE;
}
bool list_del(struct List *l, u8 index)
{
	l->item_delete(get_item_addr(l, index));
	return TRUE;
}
void *list_get(struct List *l, u8 index)
{
	return get_item_addr(l, index);
}

```

调用的时候，参考如下:

```c
typedef struct {
	int counter;
	u8 msg;
}De;
bool item_valid(De *d)
{
	return d->msg != 0xff;
}
void item_delete(De *d)
{
	d->msg = 0xff;
}
void test_array_list()
{
	printf("%d\n", sizeof(struct List));
	printf("%d\n", sizeof(u8));
	struct List *ll = list_create(sizeof(De), item_delete, item_valid);
	De d1 = { 1,1 }, d2 = { 2,2 };
	list_add(ll, (void*)&d1);
	list_add(ll, (void*)&d2);
	list_del(ll, 0);
}
```

这样就避免了频繁的内存动态分配。

上面的两个技巧仅供参考，代码也不完整，只在提供思路，希望对大家有帮助。