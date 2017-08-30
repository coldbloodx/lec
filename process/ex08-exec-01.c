#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

char* env_init[] = { "USER=unknown", "PATH=/tmp", NULL};

int main()
{
    pid_t pid;

    if((pid = fork()) < 0)
    {
        perror("error on fork 1,");
    }
    else if(pid == 0)
    {
        if(execle("/bin/echo", "echo", "arg1", "arg2", (char*)0, env_init) < 0)
        {
            perror("error on exec 1");
        }
    }

    if(waitpid(pid, NULL, 0) < 0)
    {
        perror("error on wait");
    }


    if((pid = fork()) < 0)
    {
        perror("error on fork 2,");
    }
    else if(pid == 0)
    {
        if(execlp("echo", "echo", "only arg1", (char*)0) < 0)
        {
            perror("error on exec 2");
        }
    }


    return 0;
}
            
