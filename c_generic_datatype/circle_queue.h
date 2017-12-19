#ifndef CIRCLE_QUEUE_H
#define CIRCLE_QUEUE_H
#define BUF_SZ 16
typedef struct {
	int head;
	int tail;
	int count;
	int struct_sz;
	void* array[BUF_SZ]; //pointer of data type
}Queue;

Queue *queue_create(int struct_sz); //size of data type
void queue_free(Queue *q);
int queue_push(Queue *q, void *element);
int queue_pop(Queue *q, void *element);
#endif
