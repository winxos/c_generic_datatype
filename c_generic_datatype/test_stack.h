#pragma once
#include "stack.h"
typedef struct{
    char s[10];
    int a;
}Item;
bool test_list()
{
    struct Stack stack;
    Item i1={"stack",3};
    Item i2={"nice",10};
    Item i;
    const int list_len=10;
    Item buf[list_len];
    stack_ops.init(&stack, list_len, sizeof(Item), buf);
    stack_ops.push(&stack, &i1);
    stack_ops.push(&stack, &i2);

    puts("LIST TEST START...");
    printf("PUSH, STACK SIZE:%d\n",stack_ops.size(&stack));
    if(stack_ops.size(&stack) != 2)
    {
        return FALSE;
    }
    stack_ops.pop(&stack, &i);
    printf("POP, STACK SIZE:%d\n",stack_ops.size(&stack));
    if(strcmp((void*)i.s,"nice")!=0)
    {
        return FALSE;
    }
    stack_ops.peek(&stack, &i);
    printf("PEEK, a:%d\n",i.a);
    if(i.a!=10)
    {
        return FALSE;
    }
    stack_ops.pop(&stack, &i);
    if(stack_ops.pop(&stack, &i) != FALSE)
    {
        return FALSE;
    }
    stack_ops.push(&stack, &i1);
    stack_ops.clear(&stack);
    printf("CLEAR, STACK SIZE:%d\n",stack_ops.size(&stack));
    if(stack_ops.size(&stack) != 0)
    {
        return FALSE;
    }
    return TRUE;
}