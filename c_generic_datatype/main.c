#include "test_circle_queue.h"
#include "test_stack.h"

int main(int argc, char **argv)
{
    if(test_cq()==TRUE)
    {
        puts(":)circle queue test passed.");
    }
    else
    {
        puts("!!circle queue test failed.");
    }
    puts("***********************");
    if(test_list()==TRUE)
    {
        puts(":)stack test passed.");
    }
    else
    {
        puts("!!stack test failed.");
    }
	return 0;
}
