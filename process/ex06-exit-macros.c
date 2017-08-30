#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>


void pr_exit(int status)
{
    if(WIFEXITED(status))
    {
        printf("Normal termination, exit status = %d \n", WEXITSTATUS(status));
    }
    else if(WIFSIGNALED(status))
    {
        char* core_string = WCOREDUMP(status) ? "core file generated" : "";
        printf("Abnormal termination, signal number = %d,%s \n", WTERMSIG(status), core_string);
    }
    else if(WIFSTOPPED(status))
    {
        printf("Child stopped, signal number: %d\n", WSTOPSIG(status));
    }
    return;
}

int main()
{
    pid_t pid;
    int status;

    if((pid = fork()) < 0)
    {
        perror("fork error");
    }
    else if(pid == 0)
    {
        exit(7);
    }
    if(wait(&status) != pid)
    {
        perror("wait error");
    }
    pr_exit(status);


    if((pid = fork()) < 0)
    {
        perror("fork error");
    }
    else if(pid == 0)
    {
        abort();
    }
    if(wait(&status) != pid)
    {
        perror("wait error");
    }
    pr_exit(status);


    if((pid = fork()) < 0)
    {
        perror("fork error");
    }
    else if(pid == 0)
    {
        status /= 0;
    }
    if(wait(&status) != pid)
    {
        perror("wait error");
    }
    pr_exit(status);

    return 0;
}

