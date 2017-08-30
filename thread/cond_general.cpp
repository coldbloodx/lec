//============================================================================
// Name        : condition-general.cpp
// Author      : Leo.C.Wu@NavyBlue
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <sys/time.h>
#define THREAD_NUMBER 2
using namespace std;

static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * thread1(void * arg)
{
    pthread_mutex_lock(&mutex);
    cout<<"Thread 1 locked the mutex"<<endl;
    cout<<"Thread 1  is waiting for condition signal..."<<endl;
    pthread_cond_wait(&cond,&mutex);
    cout<<"Thread 1 received condition signal!"<<endl;
    cout<<"Thread 1 unlocked the mutex"<<endl;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void * thread2(void * arg)
{
	sleep(10);
    int i = 0;
    timeval oldTime,newTime;
    gettimeofday(&oldTime,NULL);
    newTime = oldTime;
    pthread_mutex_lock(&mutex);
    cout<<"thread 2 locked the mutex"<<endl;
    while ((newTime.tv_sec- oldTime.tv_sec) <5)
    {
        sleep(1);
        gettimeofday(&newTime,NULL);
        i++;
        cout<<"thread 2 sleep "<<i<<"seconds"<<endl;
    }
    cout<<"thread 2 calls pthread_cond_signal..."<<endl;
    pthread_cond_signal(&cond);
    cout<<"unlock mutex"<<endl;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main()
{
    int i;
    int retValue;
    pthread_t pt[THREAD_NUMBER];
    retValue = pthread_create(&pt[0],NULL,thread1,NULL);
    if (retValue)
    {
        cout<<"pthread create error!"<<endl;
        exit(1);
    }
    else
    {
        cout<<"pthread1 create done!"<<endl;
    }
    retValue = pthread_create(&pt[1],NULL,thread2,NULL);
    if (retValue)
    {
        cout<<"pthread create error!"<<endl;
        exit(1);
    }
    else
    {
        cout<<"pthread2 create done!"<<endl;
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
