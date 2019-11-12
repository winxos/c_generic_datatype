#pragma once
#include "circle_queue.h"

typedef struct {
	char *s;
	void(*action)(char* s);
}Sd;
static void action(char *s)
{
	printf("do action:%s\n",s);
}
bool test_cq(void)
{
	struct CircleQueue q1;
	const int slen=10;
	Sd s1_buf[slen];
    circle_queue_ops.init(slen, sizeof(Sd), &q1, s1_buf);
    Sd s1={"hello", action};
    Sd s2={"queue", action};

    puts("CIRCLE QUEUE TEST START...");
    circle_queue_ops.inqueue(&q1, &s1);
    circle_queue_ops.inqueue(&q1, &s2);
	printf("INIT, Q size:%d\n",circle_queue_ops.size(&q1));
	if(circle_queue_ops.size(&q1)!=2)
    {
	    return FALSE;
    }
    Sd ss;
    circle_queue_ops.dequeue(&q1, &ss);
    printf("POP, Q size:%d\n",circle_queue_ops.size(&q1));
    ss.action(ss.s);
	if(strcmp(ss.s,"hello")!=0)
    {
	    return FALSE;
    }
    circle_queue_ops.peek(&q1,&ss);
    printf("PEEK, Q size:%d\n",circle_queue_ops.size(&q1));
    if(strcmp(ss.s,"queue")!=0)
    {
        return FALSE;
    }
    if(circle_queue_ops.size(&q1)!=1)
    {
        return FALSE;
    }
    circle_queue_ops.dequeue(&q1, &ss);
    printf("POP, Q size:%d\n",circle_queue_ops.size(&q1));
    ss.action(ss.s);
    if(circle_queue_ops.dequeue(&q1, &ss) != FALSE)
    {
        return FALSE;
    }
    circle_queue_ops.inqueue(&q1, &s1);
    circle_queue_ops.clear(&q1);
    printf("CLEAR, Q size:%d\n",circle_queue_ops.size(&q1));
    if(circle_queue_ops.size(&q1)!=0)
    {
        return FALSE;
    }
    return TRUE;
}