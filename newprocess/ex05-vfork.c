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
    printf("befor vfork\n");

    if((pid = vfork()) < 0)
    {
        perror("fork error");
    }
    else if(pid == 0)
    {
        glob++;
        var++;
        _exit(0);
    }
    printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
    return 0;
}
