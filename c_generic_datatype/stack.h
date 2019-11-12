#pragma once
#include "typedef.h"
struct Stack{
    u32 max_length;
	u32 item_size;
    u32 count;
	u8* data;
};
typedef struct{
    void (*init)(struct Stack *list, u32 max_length, u32 item_size, void * buf);
    bool (*push)(struct Stack *list, void *item);
    bool (*pop)(struct Stack *list, void *item);
    bool (*peek)(struct Stack *list, void *item);
    void (*clear)(struct Stack *list);
    u32 (*size)(struct Stack *list);
}StackOps;
extern StackOps stack_ops;
