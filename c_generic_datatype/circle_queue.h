#ifndef CIRCLE_QUEUE_H
#define CIRCLE_QUEUE_H
#define BUF_SZ 16
typedef struct {
	int head;
	int tail;
	int count;
	int struct_sz;
	void* array[BUF_SZ]; //pointer of data type
}CircleQueue;

CircleQueue *queue_create(int struct_sz); //size of data type
void queue_free(CircleQueue *q);
int queue_push(CircleQueue *q, void *element);
int queue_pop(CircleQueue *q, void *element);
void *queue_peek(CircleQueue *q, int index);
#endif
