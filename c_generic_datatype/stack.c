#include "stack.h"
static inline void* get_current_address(struct Stack *l)
{
	return l->data + l->count*l->item_size;
}

void list_init(struct Stack *list, u32 max_length, u32 item_size, void * buf)
{
    list->max_length=max_length;
    list->count=0;
    list->data=buf;
    list->item_size=item_size;
}
bool list_push(struct Stack *list, void *item)
{
    if(list->count==list->max_length)
    {
        return FALSE;
    }
    memcpy(get_current_address(list),item,list->item_size);
    list->count++;
}
bool list_pop(struct Stack *list, void *item)
{
    if(list->count==0)
    {
        return FALSE;
    }
    list->count--;
    memcpy(item,get_current_address(list),list->item_size);
}
bool list_peek(struct Stack *list, void *item)
{
    if(list->count==0)
    {
        return FALSE;
    }
    memcpy(item,get_current_address(list),list->item_size);
}
void list_clear(struct Stack *list)
{
    memset(list,0,sizeof(struct Stack));
}
u32 list_size(struct Stack *list)
{
    return list->count;
}
StackOps stack_ops={
        .init=list_init,
        .push=list_push,
        .pop=list_pop,
        .clear=list_clear,
        .peek=list_peek,
        .size=list_size,
};