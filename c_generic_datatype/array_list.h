#pragma once
#include "public.h"
#define MAX_LIST_COUNT 4
#pragma pack(1)
struct List{
	u8 item_size;
	u8 count;
	bool(*item_valid)(void *item);
	void(*item_delete)(void *item);
	u8* data; //pointer of data type
};
#pragma pack() 
struct List *list_create(int item_size, void(*item_delete)(void *),bool (*item_valid)(void*));
bool list_add(struct List *l, void *item);
bool list_del(struct List *l, u8 index);
void *list_get(struct List *l, u8 index);