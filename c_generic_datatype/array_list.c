#pragma once
#include "array_list.h"
static inline void* get_item_addr(struct List *l, u8 index)
{
	return l->data + index*l->item_size;
}
struct List *list_create(int item_size,void (*item_delete)(void *), bool(*item_valid)(void *))
{
	u8 i;
	struct List *list = malloc(sizeof(struct List));
	list->data = malloc(MAX_LIST_COUNT * item_size);
	list->count = 0;
	list->item_delete = item_delete;
	list->item_valid = item_valid;
	list->item_size = item_size;
	for (i = 0;i < MAX_LIST_COUNT;i++)
	{
		item_delete(get_item_addr(list, i));
	}
	return list;
}

bool list_add(struct List *l, void *item)
{
	u8 i;
	for (i = 0;i < MAX_LIST_COUNT;i++)
	{
		if (!l->item_valid(get_item_addr(l,i)))
		{
			memcpy((void*)get_item_addr(l,i),item, l->item_size);
			return TRUE;
		}
	}
	return FALSE;
}
bool list_del(struct List *l, u8 index)
{
	l->item_delete(get_item_addr(l, index));
	return TRUE;
}
void *list_get(struct List *l, u8 index)
{
	return get_item_addr(l, index);
}
