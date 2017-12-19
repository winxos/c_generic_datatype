/*
generic circle queue in c
winxos 2017/12/19
*/
#include "circle_queue.h"
#include <stdlib.h>
#include <string.h>
Queue *queue_create(int struct_sz)
{
	Queue *q = malloc(sizeof(Queue));
	for (int i = 0;i < BUF_SZ;i++)
	{
		q->array[i] = calloc(1,struct_sz);
	}
	q->head = 0;
	q->tail = 0;
	q->struct_sz = struct_sz;
	return q;
}

void queue_free(Queue *q)
{
	if (q != NULL) {
		for (int i = 0;i < BUF_SZ;i++)
		{
			free(q);
		}
	}
	free(q);
}

int queue_push(Queue *q, void *element)
{
	memcpy(q->array[q->head], element, q->struct_sz);
	q->head++;
	return 0;
}

int queue_pop(Queue *q, void *element)
{
	if (q->tail == q->head)
	{
		return -1;
	}
	memcpy(element, q->array[q->tail], q->struct_sz);
	q->tail++;
	return 0;
}
