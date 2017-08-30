#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    if((pid = fork()) < 0)
    {
        perror("error fork");
    }
    else if(pid == 0)
    {
        //first child
        if((pid = fork()) < 0)
        {
            perror("error fork");
        }
        else if(pid > 0)
        {
            printf("child of first process , parent pid = %d, self pid: %d \n", getppid(), getpid());
            return 0;
        }
        else
        {
            //child's child
            sleep(2);
            printf("child's child, parent pid = %d, self pid: %d \n", getppid(),getpid());
            return 0;
        }
    }
    printf("first process, pid: %d\n", getpid());
    if(waitpid(pid, NULL, 0) != pid)
    {
        perror("error wait");
    }
    return 0;
}
