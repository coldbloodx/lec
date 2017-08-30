#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

#include <unistd.h>
#include <pthread.h>
#include <signal.h>


int number = 0;
int tret_val1 = 1;
int tret_val2 = 2;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void sig(int signo)
{
    cout<<"signal ctrl+c(interrupt) received!!!"<<endl;
    exit(0);
}

//thread1 print even numbers
void* tfun1(void*)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        if( 0 == ( number % 2 ))
        {
            pthread_cond_wait(&cond, &mutex);
        }
        else
        {
            cout<<"Thread 1: "<<++number<<"."<<endl;
            sleep(1);
            pthread_cond_signal(&cond);
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit((void*)(&tret_val1));

}

//thread1 print odd numbers
void* tfun2(void*)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        if( 0 != ( number % 2 ))
        {
            pthread_cond_wait(&cond, &mutex);
        }
        else
        {
            cout<<"Thread 2: "<<++number<<"."<<endl;
            sleep(1);
            pthread_cond_signal(&cond);
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit((void*)(&tret_val2));
}


int main()
{
    pthread_t tid1, tid2;
    void* tret_val1;
    void* tret_val2;
    int ret_val = 0;

    signal(SIGINT, sig);
    cout<<"Program will start in 3 seconds, press ctrl+c to terminate."<<endl;
    sleep(3);

    ret_val = pthread_create(&tid1, NULL, tfun1, NULL);
    if(ret_val)
    {
        perror("create thread 1 error:");
    }

    ret_val = pthread_create(&tid2, NULL, tfun2, NULL);
    if(ret_val)
    {
        perror("create thread 2 error:");
    }

    pthread_join(tid1, &tret_val1);
    cout<<"thread 1 exit with code:"<<*((int*)(tret_val1))<<endl;
    
    pthread_join(tid2, &tret_val2);
    cout<<"thread 2 exit with code:"<<*((int*)(tret_val2))<<endl;
    return 0;
}
