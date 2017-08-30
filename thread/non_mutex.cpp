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

int sum = 0;

void * thread1(void * arg)
{
	for (int i = 0; i < 100000; ++i)
	{
		//sum += 10;
		sum = sum + 10;
		cout<<"sum in thread1:"<<sum<<endl;
	}
	return NULL;
}

void * thread2(void * arg)
{
	for (int i = 0; i < 100000; ++i)
	{
		//sum -= 10;
		sum = sum - 10;
		cout<<"sum in thread2:"<<sum<<endl;
	}
	return NULL;
}

int main()
{
	pthread_t pt1;
	pthread_t pt2;
	if (pthread_create(&pt1, NULL, thread1, NULL))
	{
		cout << "pthread_create error!" << endl;
		exit(1);
	}
	else
	{
		cout << "pthread_create done!" << endl;
	}
	if (pthread_create(&pt2, NULL, thread2, NULL))
	{
		cout << "pthread_create error!" << endl;
		exit(1);
	}
	else
	{
		cout << "pthread_create done!" << endl;
	}

	pthread_join(pt1, NULL);
	pthread_join(pt2, NULL);
	cout<<"final sum:"<<sum<<endl;
	return 0;
}
