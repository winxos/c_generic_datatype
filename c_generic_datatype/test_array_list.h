#pragma once
#include "share.h"
typedef struct {
	int counter;
	u8 msg;
}De;
void test_array_list()
{
	printf("%d\n", sizeof(struct List));
	printf("%d\n", sizeof(u8));
	struct List *ll = list_create(sizeof(De));
}