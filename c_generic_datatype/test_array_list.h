#pragma once
#include "array_list.h"
#include "circle_queue.h"
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
typedef enum {
	E0,E1,E2,E3,E_NOT_USE
}E;
bool item_valid2(E *d)
{
	return *d != E_NOT_USE;
}
void item_delete2(E *d)
{
	*d = E_NOT_USE;
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
	struct List *l2 = list_create(sizeof(long long), item_delete2, item_valid2);
	long long a = 2, b = 8;
	list_add(l2, &a);
	list_add(l2, &b);
	list_del(l2, 1);
	int *c=list_get(l2, 0);
}