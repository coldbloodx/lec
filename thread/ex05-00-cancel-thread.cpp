//============================================================================
// Name        : ex05-00-cancel-thread.cpp
// Author      : Leo.C.Wu@NavyBlue
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
using namespace std;

const int THREAD_NUMBER  = 2;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_t pt[THREAD_NUMBER];

void * thread1(void * arg)
{
    //主义这里的PTHREAD_CANCEL_ENABLE表示线程可以撤销，否则不能撤销。
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
    pthread_mutex_lock(&mutex);
    sleep(5);
    cout<<"now thread 1 is in cancelation point..."<<endl;
    //pthread_cond_wait是一个撤销点，
    //thread1在这里等待条件变量的满足
    pthread_cond_wait(&cond,&mutex);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void * thread2(void * arg)
{
    cout<<"thread 2 sends cancelation request to thread 1"<<endl;
    //send cancel request to thread 1
    pthread_cancel(pt[0]);
    cout<<"thread 2 ends"<<endl;
    pthread_exit(NULL);
}

int main()
{
    int i;
    int retValue;
    retValue = pthread_create(&pt[0],NULL,thread1,NULL);
    if (retValue)
    {
        cout<<"pthread 1 create error!"<<endl;
        exit(1);
    }
    else
    {
        cout<<"pthread 1 create done!"<<endl;
    }
    retValue = pthread_create(&pt[1],NULL,thread2,NULL);
    if (retValue)
    {
        cout<<"pthread 2 create error!"<<endl;
        exit(1);
    }
    else
    {
        cout<<"pthread 2 create done!"<<endl;
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
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}
