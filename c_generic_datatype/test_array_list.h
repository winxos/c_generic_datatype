#pragma once
#include "share.h"
typedef struct {
	int counter;
	u8 msg;
}De;
bool item_valid(De *d)
{
	return d->msg != 0xff;
}
void item_delete(De *d)
{
	d->msg = 0xff;
}
void test_array_list()
{
	printf("%d\n", sizeof(struct List));
	printf("%d\n", sizeof(u8));
	struct List *ll = list_create(sizeof(De), item_delete, item_valid);
	De d1 = { 1,1 }, d2 = { 2,2 };
	list_add(ll, (void*)&d1);
	list_add(ll, (void*)&d2);
	list_del(ll, 0);
}