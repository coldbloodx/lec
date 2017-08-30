#include <stdio.h>
#include <signal.h>

void sig()
{
    printf("signal received!!!\n");
    return ;
}

int intcounter = 0;

void sigint()
{
    printf("signal int received!!!\n");
    intcounter ++ ;
    printf("int counter: %d", intcounter);
    return ;
}

int main()
{
    signal(SIGTERM, sig);
    signal(SIGINT, sigint);
    printf("start main function\n");
    int counter = 0;
    while(1)
    {
        counter++;
        printf("counter: %d\n", counter);
        sleep(1);
    }
    return 0;
}
