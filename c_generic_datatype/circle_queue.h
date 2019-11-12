#ifndef CIRCLE_QUEUE_H
#define CIRCLE_QUEUE_H

#include "typedef.h"

struct CircleQueue
{
    u32 head;
    u32 tail;
    u32 length;
    u32 item_size;
    u32 count;
    u8 *data; //storage
};
typedef struct
{
    void (*init)(u32 length, u32 item_size,struct CircleQueue *q,void* data);
    void (*clear)(struct CircleQueue *q);
    bool (*inqueue)(struct CircleQueue *q, void *item);
    bool (*dequeue)(struct CircleQueue *q, void *item);
    bool (*peek)(const struct CircleQueue *q,void *item);
    u32 (*size)(const struct CircleQueue *q);
    void (*serialize)(const struct CircleQueue *q, u8 *out, u32 *len);
    void (*deserialize)(struct CircleQueue *q, void *data, u8 *in);
}CircleQueueOps;
extern CircleQueueOps circle_queue_ops;
#endif
