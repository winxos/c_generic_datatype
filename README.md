# C语言抽象数据类型的实现

> modify:wvv 20191112
>
> create:wvv 20171223

### 前言

在C语言中，由于没有默认泛型支持，在实现数据结构的时候通常会和具体承载内容挂钩。

例如：按常规数据结构书上描述来设计一个栈，那么栈里面放置的内容类型是确定的，比如是int，或者某种结构体类型。虽然我们可以通过 **typedef**的技巧对栈实际类型进行替换，使得栈可以在不同场合装入不同内容，但是在同一工程下栈无法装载不同的数据类型，这样使得如果有几个不同数据类型的栈，就需要把栈代码再实现多份，这样就实际上没有实现栈这个抽象数据类型本身的抽象目的。

要实现一个通用类型的抽象数据结构库，需要考虑几个问题：

1. 多种数据的支持性
2. 接口的合理性
3. 跨平台支持性
4. 特殊使用环境考虑，例如MISRA标准规定嵌入式上一般不能用动态内存分配。
5. 等

因为C语言语法简单，不像C++等高级语言自身拥有很多特性容易实现真正的抽象数据类型，所以想要非常好的实现抽象数据类型，需要很多的技巧性，对于刚学会c大学课堂上那些知识来说的朋友可能无从下手，网上这方面教程非常少，本文抛砖引玉，给初学者一些启迪。

### 抽象的实现：void* （空指针）转换法

该技巧利用C语言中空指针无数据类型，可以进行强制转换的特点来实现任意数据类型的抽象。

以结构体数组循环队列为例，声明如下：

```c
typedef struct {
	uint32_t head;
	uint32_t tail;
	uint32_t count; /*real item counts*/
	uint32_t size;	/*queue max size*/
    uint32_t item_size; /*item each size in bytes*/
	uint8_t * buf; /*storage place*/
}CircleQueue;
CircleQueue *queue_create(uint32_t item_size, uint32_t size);
bool queue_push(CircleQueue *q, void *element);
bool queue_pop(CircleQueue *q, void *element);
bool queue_peek(CircleQueue *q, void *element);
/*注：uint32_t 表示32位无符号类型*/
/*注：uint8_t 表示8位无符号类型*/
```

核心思想：

将任意数据类型都通过void* 指针转换为uint8_t类型进行内部存储，因为计算机内部最小存储单位为uint8_t，对于抽象数据结构而言，任何类型本指上是一定字节数量的一块内存区域，所以不同的数据类型都抽象成为不同个数的uint8_t类型的操作，只是对于不同宽度数据每次计算偏移量不一样而已。这样就实现了任意类型的抽象。

队列具体实现过程：

- `通过queue_create创建队列，传入单个对象所占内存数、队列最大容量，系统内部动态分配大小为item_size*size内存给buf，返回创建的队列指针。`
- `push操作时，通过void*类型将任意类型数据传入，系统内部可以根据count以及item_size值计算出对象在buf中的实际存储位置，然后进行赋值传入。`
- `pop操作时，系统内部可以根据count以及item_size值计算出所需对象在buf中的实际存储位置，然后通过void*类型进行赋值导出。`

- 其他操作类似。


参考调用方式如下：

```c
typedef struct {
	int a;
	void(*action)(char* param);
}Sd;
typedef struct {
	int a;
	char b[15];
}S2;
void test_cq(void)
{
	Sd a = { 1,f };
	S2 b = { 1,"hhggggggh" };
	CircleQueue *q1 = queue_create(sizeof(Sd),10);/*创建最大容量为10的Sd类型队列*/
	CircleQueue *q2 = queue_create(sizeof(S2),5);/*创建最大容量为5的S2类型队列*/
	queue_push(q1, (void*)&a);
	queue_push(q2, (void*)&b);
    queue_pop(q1,&a);
}
```

注意的是结构体指针转成void* 指针需要进行强制转换，不然会有警告。

### 不使用动态内存分配的实现方式

动态内存分配涉及到内存管理，分配，销毁等，如果操作不当，很容易造成内存泄漏，内存碎片过多等，是造成BUG的重要成因，所以在安全性高的一些嵌入式场合，嵌入式领域MISRA标准是不允许使用动态内存分配的，整个系统必须要在初始化完成后内存分配就完全确定，不能再发生变化。

具体应该如何实现全静态分配的抽象数据结构呢？

我们只需要做一点改变，数据结构以前防数据的buf区改为一个指针，指向用户自己在外部分配好内存区域，其他不变。

下面我们以一个具体栈为例，进行说明：

``` c
struct Stack{
    u32 max_length;
	u32 item_size;
    u32 count; /*real items count*/
	u8* data; /*pointer to the real external address*/
};
void list_init(struct Stack *list, u32 max_length, u32 item_size, void * buf)
{
    list->max_length=max_length;
    list->count=0;
    list->data=buf;
    list->item_size=item_size;
}
```

我们通过list_init 完成stack的初始化，使用的时候我们声明空的Stack，然后作为第一参数传入list_init 中，同时传入栈最大容量，对象的大小，以及对象所在的缓存就完成了初始化。

```c
typedef struct{
    char s[10];
    int a;
}Item;
int test()
{
    const int list_len=10; /*max size*/
    Item buf[list_len]; /*buffer*/
    struct Stack stack;
    list_init(&stack, list_len, sizeof(Item), buf); /*init*/
}
```

上面的代码演示了初始化的过程，其他操作与前一章节类似。

至此我们就实现了完全的**抽象数据类型**以及**全静态内存抽象数据类型**。

### 抽象数据操作接口的统一

对于一个抽象数据结构来说，对应的会有一系列的操作方法（函数），但是用户层不一定知道确切的函数名称，这样用户必须对照着头文件来进行调用，更科学的办法是我们将需要提供给用户的操作集中定义在一个结构体里面，这有点像高级语言中的接口定义，用户通过统一的接口进行调用，这样要方便一些，以Stack为例，接口声明如下:

```c
typedef struct{
    void (*init)(struct Stack *list, u32 max_length, u32 item_size, void * buf);
    bool (*push)(struct Stack *list, void *item);
    bool (*pop)(struct Stack *list, void *item);
    bool (*peek)(struct Stack *list, void *item);
    void (*clear)(struct Stack *list);
    u32 (*size)(struct Stack *list);
}StackOps;
extern StackOps stack_ops;
```

用户通过stack_ops来进行统一调用，调用过程如下：

```c
struct Stack stack;
Item i1={"stack",3};
Item i2={"nice",10};
const int list_len=10;
Item buf[list_len];
stack_ops.init(&stack, list_len, sizeof(Item), buf);
stack_ops.push(&stack, &i1);
stack_ops.push(&stack, &i2);
```

具体请参阅完整代码。

### 项目开发环境

本项目 [c_generic_datatype](https://github.com/winxos/c_generic_datatype/tree/master/c_generic_datatype)  文件夹内有一个完整的代码实现，包含了环形队列以及栈的实现，还有他们对应的自动测试例程，整个项目采用CLion IDE进行开发，安装好clion后，自己配置好c开发环境，clone下来后可以直接运行。

