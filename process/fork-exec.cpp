//============================================================================
// Name        : fork-exec.cpp
// Author      : Leo.C.Wu
// Version     :
// Copyright   : Leo.C.Wu@NavyBlue
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <unistd.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    char* null = (char*)(0);
    char* envp[] = { "PATH=/tmp", "USER=leo", "STATUS=testing", null };
    char* argv_execv[] = { "echo", "excuted by execv", null };
    char* argv_execvp[] = { "echo", "executed by execvp", null };
    char* argv_execve[] = { "env", null };
    if(fork()==0) 
    {
        if(execl("/bin/echo", "echo", "executed by execl", NULL)<0)
        {
            perror("Err on execl");
        }
    }
    if(fork()==0)
    {
        if(execlp("echo", "echo", "executed by execlp", NULL)<1)
        {
            perror("Err on execlp");
        }
    }
    if(fork()==0) 
    {
        if(execle("/usr/bin/env", "env", NULL, envp)<0)
        {
            perror("Err on execle");
        }
    }
    if(fork()==0) 
    {
        if(execv("/bin/echo", argv_execv)<0)
        {
            perror("Err on execv");
        }
    }
    if(fork()==0) {
        if(execvp("echo", argv_execvp)<0)
        {
            perror("Err on execvp");
        }
    }
    if(fork()==0) 
    {
        if(execve("/usr/bin/env", argv_execve, envp)<0)
        {
            perror("Err on execve");
        }
    }
    return 0;
}
