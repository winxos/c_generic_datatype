/*
generic circle queue in c/embeded c
winxos 2017/12/19
*/
#include "circle_queue.h"

void queue_init(u32 length, u32 item_size, struct CircleQueue *q, void* data)
{
    q->length = length;
    q->item_size = item_size;
    q->tail = 0;
    q->head = 0;
    q->count = 0;
    q->data = data;
}

static inline void *get_item_addr(const struct CircleQueue *q, u32 index)
{
    return q->data + index * q->item_size;
}

void queue_clear(struct CircleQueue *q)
{
    memset(q->data, 0, q->length * q->item_size);
    q->tail = 0;
    q->head = 0;
    q->count = 0;
}

bool queue_push(struct CircleQueue *q, const void *item)
{
    memcpy(get_item_addr(q, q->tail), item, q->item_size);
    q->tail++;
    if (q->tail >= q->length)
    {
        q->tail = 0;
    }
    if (q->count == q->length)/*full*/
    {
        q->head = q->tail;
    }
    else
    {
        q->count++;
    }
    return TRUE;
}

bool queue_pop(struct CircleQueue *q, void *item)
{
    if (q->count == 0)
    {
        return FALSE;
    }
    memcpy(item, get_item_addr(q, q->head), q->item_size);
    q->head++;
    if (q->head >= q->length)
    {
        q->head = 0;
    }
    q->count--;
    return TRUE;
}

bool queue_peek(const struct CircleQueue *q, void *item)
{
    if (q->count == 0)
    {
        return FALSE;
    }
    memcpy(item, get_item_addr(q, q->head), q->item_size);
    return TRUE;
}

u32 queue_size(const struct CircleQueue *q)
{
    return q->count;
}

void queue_serialize(const struct CircleQueue *q, u8 *out, u32 *len)
{
    memcpy(out, (u8*) q, sizeof(struct CircleQueue) - 4);
    memcpy(out + sizeof(struct CircleQueue) - 4, q->data, q->length * q->item_size);
    *len = sizeof(struct CircleQueue) - 4 + q->length * q->item_size;
}
void queue_deserialize(struct CircleQueue *q, void *data, u8 *in)
{
    memcpy((u8*) q, in, sizeof(struct CircleQueue) - 4);
    q->data = data;
    memcpy(data, in + sizeof(struct CircleQueue) - 4, q->length * q->item_size);
}
CircleQueueOps circle_queue_ops={
        .init=queue_init,
        .clear=queue_clear,
        .inqueue=queue_push,
        .dequeue=queue_pop,
        .peek=queue_peek,
        .size=queue_size,
        .serialize=queue_serialize,
        .deserialize=queue_deserialize

};