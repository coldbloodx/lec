//============================================================================
// Name        : ex03-mutex.cpp
// Author      : Leo.C.Wu@NavyBlue
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <pthread.h>
#include <cstdlib>

using namespace std;

//add a lock to do data sync
static pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;


int sum = 0;

void * thread1(void * arg)
{

	for (int i = 0; i < 100000; ++i)
	{
		pthread_mutex_lock(&mutex1);
		sum += 10;
		cout<<"sum in thread1:"<<sum<<endl;
		pthread_mutex_unlock(&mutex1);
	}

	return NULL;
}

void * thread2(void * arg)
{
	for (int i = 0; i < 100000; ++i)
	{
		pthread_mutex_lock(&mutex1);
		sum -= 10;
		cout<<"sum in thread2:"<<sum<<endl;
		pthread_mutex_unlock(&mutex1);
	}
	return NULL;
}

int main()
{
	pthread_t pt1;
	pthread_t pt2;
	if (pthread_create(&pt1, NULL, thread1, NULL))
	{
		cerr << "pthread_create error!" << endl;
		exit(1);
	}
	else
	{
		cout << "pthread_create done!" << endl;
	}
	if (pthread_create(&pt2, NULL, thread2, NULL))
	{
		cerr << "pthread_create error!" << endl;
		exit(1);
	}
	else
	{
		cout << "pthread_create done!" << endl;
	}

	pthread_join(pt1, NULL);
	pthread_join(pt2, NULL);

	pthread_mutex_destroy(&mutex1);

	cout << "sum:" << sum << endl;

	return 0;
}

