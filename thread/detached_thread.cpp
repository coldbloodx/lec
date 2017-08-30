#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <cstdio>
using namespace std;

int makethread(void* (fn)(void*), void* arg)
{
    int err;
    pthread_t tid;
    pthread_attr_t attr;

    err = pthread_attr_init(&attr);
    if(err != 0)
    {
        return err;
    }
    err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if(err == 0)
    {
        sleep(1);
        err = pthread_create(&tid, &attr, fn, arg);
    }
    pthread_attr_destroy(&attr);
    return err;
}

void* add(void* arg)
{
    printf("in function add\n");
    return (void*)NULL;
}

int main()
{
    makethread(add, NULL);
    sleep(1);
    return 0;
}
