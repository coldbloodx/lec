#include <stdio.h>
#include <stdlib.h>
#include <linux/sched.h>
#include <unistd.h>
#include <signal.h>
#define FIBER_STACK 8192

int global_var;
void * stack;
int do_something()
{
    printf("This is son, the pid is:%d, the global_var is: %d\n", getpid(), ++global_var);
    free(stack); 
    exit(0);
}

int main() 
{
    void * stack;
    global_var = 1;
    stack = malloc(FIBER_STACK);
    if(!stack) 
    {
        printf("The stack failed\n");
        exit(0);
    }
    printf("creating son thread!!!\n");
    clone(&do_something, (char *)stack + FIBER_STACK, CLONE_VM | CLONE_VFORK, 0);
    printf("This is parent,father my pid is: %d, the global_var is: %d\n", getpid(), global_var);
    exit(0);
}
