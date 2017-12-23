#pragma once
#include "public.h"
#define MAX_LIST_COUNT 4
#pragma pack(1)
struct List{
	u8 item_size;
	u8 count;
	void* data[MAX_LIST_COUNT]; //pointer of data type
};
#pragma pack(pop) 
struct List *list_create(int item_size);
bool list_add(struct List *l, void *item);
bool list_del(struct List *l, u8 index);
void *list_get(struct List *l, u8 index);