//============================================================================
// Name        : fork.c
// Author      : Leo.C.Wu
// Version     :
// Copyright   : Leo.C.Wu@NavyBlue
// Description : Hello World in C, Ansi-style
//============================================================================



#include <unistd.h>
#include <stdio.h>

int glob = 6;
char buf[] = "test write to std out\n";


int main()
{
    int var;
    pid_t pid;

    var = 88;
    if(write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) -1)
    {
        perror("write error");
    }
    printf("befor fork\n");

    if((pid = fork()) < 0)
    {
        perror("fork error");
    }
    else if(pid == 0)
    {
        glob++;
        var++;
    }
    else
    {
        sleep(2);
    }
    printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
    return 0;
}
