/*
generic circle queue in c/embeded c
winxos 2017/12/19
*/
#include "share.h"

CircleQueue *queue_create(int struct_sz)
{
	CircleQueue *q = malloc(sizeof(CircleQueue));
	for (int i = 0;i < BUF_SZ;i++)
	{
		q->array[i] = calloc(1,struct_sz);
	}
	q->head = 0;
	q->tail = 0;
	q->count = 0;
	q->struct_sz = struct_sz;
	return q;
}

void queue_free(CircleQueue *q)
{
	if (q != NULL) {
		for (int i = 0;i < BUF_SZ;i++)
		{
			free(q);
		}
	}
	free(q);
}

int queue_push(CircleQueue *q, void *element)
{
	memcpy(q->array[q->head], element, q->struct_sz);
	q->head++;
	if (q->head >= BUF_SZ)
	{
		q->head = 0;
		//error
	}
	if (q->count < BUF_SZ)
	{
		q->count++;
	}
	return 0;
}

int queue_pop(CircleQueue *q, void *element)
{
	if (q->count <=0)
	{
		return -1;
	}
	memcpy(element, q->array[q->tail], q->struct_sz);
	q->tail++;
	if (q->tail >= BUF_SZ)
	{
		q->tail = 0;
	}
	q->count--;
	return 0;
}
void *queue_peek(CircleQueue *q, int index)
{
	return (void *)q->array[index];
}
