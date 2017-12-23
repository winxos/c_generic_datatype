#pragma once
#include "share.h"
typedef struct {
	int a;
	void(*action)(char* param);
}S1;
typedef struct {
	int a;
	char b[15];
}S2;
void f(char *s)
{
	printf(s);
}
void test_cq(void)
{
	static CircleQueue *q1, *q2;
	S1 a = { 1,f };
	S2 b = { 1,"hhggggggh" };
	q1 = queue_create(sizeof(S1));
	q2 = queue_create(sizeof(S2));
	queue_push(q1, (void*)&a);
	queue_push(q2, (void*)&b);
	queue_push(q2, (void*)&b);
	S2 *s = queue_peek(q2, q2->tail);
	s->a = 2;
	S1 c;
	S2 d = { 0,"" };
	queue_pop(q1, &c);
	queue_pop(q2, &d);
	c.action("hello world\n");
}