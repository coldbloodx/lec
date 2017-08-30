#include <unistd.h>
#include <cstdio>
#include <pthread.h>
#include <iostream>
using namespace std;
int tret_val1 = 1;
int tret_val2 = 2;


void* thr_fun1(void* arg)
{
    printf("thread 1 returning\n");
    return ((void *)&tret_val1);
}

void* thr_fun2(void* arg)
{
    printf("thread 2 returning\n");
    return ((void *)&tret_val2);
}


int main()
{
    int err;
    pthread_t tid1, tid2;
    void* tret;
    err = pthread_create(&tid1, NULL, thr_fun1, NULL);
    if(err != 0)
    {
        perror("thread1 create");
    }

    err = pthread_create(&tid2, NULL, thr_fun2, NULL);
    if(err != 0)
    {
        perror("thread2 create");
    }
    err =  pthread_join(tid1, &tret);
    if(err !=0)
    {
        perror("join thread1");
    }
    printf("thread 1 exit code: %d\n", *(int*)tret);
    err = pthread_join(tid2, &tret);
    if(err !=0)
    {
        perror("join thread2");
    }
    printf("thread 2 exit code: %d\n", *(int*)tret);

    return 0;
}
