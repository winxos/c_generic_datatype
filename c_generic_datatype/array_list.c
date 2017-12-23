#pragma once
#include "array_list.h"

struct List *list_create(int item_size)
{
	struct List *list = malloc(sizeof(struct List));
	u8 i;
	for (i = 0; i < MAX_LIST_COUNT; i++)
	{
		list->data[i] = calloc(1, item_size);
	}
	list->count = 0;
	list->item_size = item_size;
	return list;
}
bool list_add(struct List *l, void *item)
{

	return TRUE;
}
bool list_del(struct List *l, u8 index)
{
	return TRUE;
}
void *list_get(struct List *l, u8 index)
{
	return l->data[index];
}
