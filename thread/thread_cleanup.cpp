#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <cstdio>
using namespace std;
int tret1 = 0;
int tret2 = 0;

void cleanup(void* arg)
{
    printf("cleanup: %s\n", (char*)arg);
}

void* thr_fn1(void* arg)
{
    printf("thread 1 start\n");
    pthread_cleanup_push(cleanup, (void*)"thread 1 first handler");
    pthread_cleanup_push(cleanup, (void*)"thread 1 second handler");
    printf("thread 1 push complete\n");
    tret1 = 1;
    if(arg)
    {
        return (void*)&tret1;
    }
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    return (void*)&tret1;
}

void* thr_fn2(void* arg)
{
    printf("thread 2 start\n");
    pthread_cleanup_push(cleanup, (void*)"thread 2 first handler");
    pthread_cleanup_push(cleanup, (void*)"thread 2 second handler");
    printf("thread 2 push complete\n");
    tret2 = 2;
    if(arg)
    {
        return (void*)&tret2;
    }
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    pthread_exit((void*)&tret2);
}

int main()
{
    int err;
    pthread_t tid1, tid2;
    void *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, (void*)1);
    if(err != 0)
    {
        perror("thread1 create");
    }
    err = pthread_create(&tid2, NULL, thr_fn2, (void*)1);
    if(err != 0)
    {
        perror("thread2 create");
    }
    err = pthread_join(tid1, &tret);
    if(err != 0)
    {
        perror("thread1 join");
    }
    printf("thread 1 exit code: %d\n", *(reinterpret_cast<int*>(tret)));
    err = pthread_join(tid2, &tret);
    if(err != 0)
    {
        perror("thread2 join");
    }
    printf("thread 2 exit code: %d\n", *(reinterpret_cast<int*>(tret)));
    return 0;
}

