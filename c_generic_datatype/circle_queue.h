#ifndef CIRCLE_QUEUE_H
#define CIRCLE_QUEUE_H
#define BUF_SZ 16
typedef struct {
	int head;
	int tail;
	int struct_sz;
	void* array[BUF_SZ];
}Queue;

Queue *queue_create(int struct_sz);
void queue_free(Queue *aqueue);
int queue_push(Queue *aqueue, void *element);
int queue_pop(Queue *aqueue, void *element);
#endif
