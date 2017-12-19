#include <stdio.h>
#include "circle_queue.h"
static Queue *q1, *q2;
static int max_len = 4;
typedef struct {
	int a, b;
}S1;
typedef struct {
	int a;
	char b[15];
}S2;
void test(void)
{
	S1 a = { 1,2 };
	S2 b = { 1,"hhggggggh" };
	q1 = queue_create(sizeof(S1));
	q2 = queue_create(sizeof(S2));
	queue_push(q1, (void*)&a);
	queue_push(q2, (void*)&b);
	S1 c = { 0,0 };
	S2 d = { 0,"" };
	queue_pop(q1, &c);
	queue_pop(q2, &d);
}
int main(int argc, char **argv)
{
	test();
	return 0;
}
