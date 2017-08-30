//============================================================================
// Name        : ex05-01-cancel-thread.cpp
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

void myCleanup(void * arg)
{
	pthread_mutex_unlock((pthread_mutex_t *)arg);
	cout<<"call myCleanup"<<endl;
}

void * thread1(void * arg)
{
    int ret_val;
    //设置撤销请求类型为PTHREAD_CANCEL_DISABLE，在设置为PTHREAD_CANCEL_ENABLE之前，
    //这其中的代码不接受来自thread2的线程撤销请求。
    ret_val = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
    if (ret_val)
    {
    	cout<<"pthread_setcancelstate error..."<<endl;
    	pthread_exit(NULL);
    }
    else
    {
    	cout<<"pthread_setcancelstate done..."<<endl;
    }
    //设置撤销类型为PTHREAD_CANCEL_DEFERRED，也就是说在thread1运行到撤销点的时侯
    //才能响应thread 2的撤销请求。
    ret_val = pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
    if (ret_val)
    {
    	cout<<"pthread_setcanceltype error..."<<endl;
    	pthread_exit(NULL);
    }
    else
    {
    	cout<<"pthread_setcanceltype done..."<<endl;
    }
    //pthread_cleanup_push(void function,void * arg)
    //这不是一个函数是一个宏，必须和后面的pthread_cleanup_pop()成对使用。
    //这个宏用来注册撤销清理函数myCleanup()，mutex是给撤销清理函数myCleanup()传递的参数。
    pthread_cleanup_push(myCleanup,(void *)&mutex);
    pthread_mutex_lock(&mutex);
    sleep(5);
    //设置PTHREAD_CANCEL_ENABLE,使之能接受撤销的请求。
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
    cout<<"now thread 1 is in cancelation point..."<<endl;
    //pthread_cond_wait是一个撤销点，
    //thread1在这里等待条件变量的满足
    pthread_cond_wait(&cond,&mutex);
    pthread_mutex_unlock(&mutex);
    //清除最近注册的清理函数，如果传递的参数是0，则表示只是清除清理例程函数；
    //如果传递的参数为1,则表示除了清除例程函数，还要执行清理函数。
    pthread_cleanup_pop(0);
    pthread_exit(NULL);
}

void * thread2(void * arg)
{
    sleep(5);
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
