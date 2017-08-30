//============================================================================
// Name        : ex07-sinal.cpp
// Author      : Leo.C.Wu@NavyBlue
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <signal.h>
#include <pthread.h>
#include <cstdlib>

using namespace std;

const int THREAD_NUMBER = 2;
pthread_t pt[THREAD_NUMBER];

void sigHandler(int signo)
{
    switch (signo)
    {
    case SIGUSR1:
    {
        cout<<"thread "<<pthread_self()<<" : in signal handler: get signal SIGUSR1"<<endl;
        break;
    }
    case SIGUSR2:
    {
        cout<<"thread "<<pthread_self()<<" : in signal handler: get signal SIGUSR2"<<endl;
        break;
    }
    default:
    {
        break;
    }
    }
}

void * thread1(void * arg)
{
    sigset_t newmask,oldmask,waitset;
    int ret_val;
    int signo;

    sigemptyset(&waitset);
    sigemptyset(&newmask);

    //initialize the signal set,and block signal SIGUSR1 while waiting for signal SIGUSR2
    sigaddset(&newmask,SIGUSR1);
    //initialize the signal set,and wait for SIGUSR2
    sigaddset(&waitset,SIGUSR2);

    cout<<"thread 1 ID is :"<<pthread_self()<<endl;

    //block signal SIGUSR1
    ret_val = pthread_sigmask(SIG_BLOCK,&newmask,&oldmask);
    if (ret_val)
    {
        cout<<"pthread_sigmask error"<<endl;
        pthread_exit(0);
    }
    else
    {
        cout<<"pthread_sigmask done"<<endl;
    }
    cout<<"pthread 1 calls sigwait"<<endl;
    sigwait(&waitset,&signo);

    if (SIGUSR2 == signo)
    {
        cout<<"in thread 1 routing: thread 1 received signal SIGUSR2"<<endl;
    }

    ret_val = pthread_sigmask(SIG_SETMASK,&oldmask,NULL);
    if (ret_val)
    {
        cout<<"pthread_sigmask SIG_SETMASK error!"<<endl;
        pthread_exit(0);
    }
    pthread_exit(0);
}

void * thread2(void * arg)
{
    sleep(1);
    cout<<"the ID of thread 2 is:"<<pthread_self()<<endl;
    pthread_kill(pt[0],SIGUSR1);
    cout<<"thread 2 has sent SIGUSR1 to thread 1"<<endl;
    pthread_kill(pt[0],SIGUSR2);
    cout<<"thread 2 has send SIGUSR2 to thread 2"<<endl;
    pthread_exit(0);
}

int main()
{
    int i;
    int retValue;

    signal(SIGUSR1,sigHandler);
    signal(SIGUSR2,sigHandler);

    retValue = pthread_create(&pt[0],NULL,thread1,NULL);
    if (retValue)
    {
        cout<<"pthread create error!"<<endl;
        exit(1);
    }
    else
    {
        cout<<"pthread create done!"<<endl;
    }
    retValue = pthread_create(&pt[1],NULL,thread2,NULL);
    if (retValue)
    {
        cout<<"pthread create error!"<<endl;
        exit(1);
    }
    else
    {
        cout<<"pthread create done!"<<endl;
    }
    for (i = 0; i< THREAD_NUMBER ; i++ )
    {
        retValue = pthread_join(pt[i],NULL);
        if (retValue)
        {
            cout<<"pthread "<<i<<" join error!"<<endl;
            exit(1);
        }
        else
        {
            cout<<"pthread "<<i<<" join done!"<<endl;
        }
    }
    return 0;
}
