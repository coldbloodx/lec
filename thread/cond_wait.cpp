//============================================================================
// Name        : cond-wait.cpp
// Author      : Leo.C.Wu@NavyBlue
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <cstdlib>

const int THREAD_NUMBER = 2;
using namespace std;

static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static int x = 0, y = 0;

void * thread1(void * arg)
{
	timeval now;
	timespec timeout;
	int retcode;
	pthread_mutex_lock(&mutex);
	gettimeofday(&now, NULL);

	//最多等待条件变量5秒
	timeout.tv_sec = now.tv_sec + 5;
	timeout.tv_nsec = now.tv_usec * 1000;
	retcode = 0;

	while (x >= y && retcode != ETIMEDOUT)
	{
		retcode = pthread_cond_timedwait(&cond, &mutex, &timeout);
	}
	if (retcode == ETIMEDOUT)
	{
		cout << "pthread_cond_timedwait timeout!" << endl;
	}
	else
	{
		cout << "thread 1 got condition signal!" << endl;
	}
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

void * thread2(void * arg)
{
	int i;
	for (i = 0; i < 5; i++)
	{
		x = rand() % 5;
		y = rand() % 5;
		sleep(1);
		cout << "x is: " << x << endl << "y is: " << y << endl;
		if (x < y)
		{
			break;
		}
	}
	pthread_mutex_lock(&mutex);
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

int main()
{
	int i;
	int retValue;
	pthread_t pt[THREAD_NUMBER];
	retValue = pthread_create(&pt[0], NULL, thread1, NULL);
	if (retValue)
	{
		cout << "pthread create error!" << endl;
		exit(1);
	}
	else
	{
		cout << "pthread create done!" << endl;
	}
	retValue = pthread_create(&pt[1], NULL, thread2, NULL);
	if (retValue)
	{
		cout << "pthread create error!" << endl;
		exit(1);
	}
	else
	{
		cout << "pthread create done!" << endl;
	}
	for (i = 0; i < THREAD_NUMBER; i++)
	{
		retValue = pthread_join(pt[i], NULL);
		if (retValue)
		{
			cout << "pthread " << i << " join error!" << endl;
			exit(1);
		}
		else
		{
			cout << "pthread " << i << " join done!" << endl;
		}
	}
	return 0;
}
