//============================================================================
// Name        : ex02-thread-properties.cpp
// Author      : Leo.C.Wu@NavyBlue
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <pthread.h>
#include <cstdlib>
using namespace std;

void * sum_val(void * arg)
{
	int sum = 0;
	int i;
	int count = *((int *) arg);
	for (i = 0; i < count; i++)
	{
		sum += i;
	}
	cout << "The sum is:" << sum << endl;
	pthread_exit(NULL);
}

int main()
{
	pthread_t pt;
	int count = 10;
	int ret_val;
	pthread_attr_t attr;

	struct sched_param sp;

	sp.sched_priority = 2;

	//初始化pthread_attr_t线程属性对象，初始化的时侯，会使用线程属性的初始值来填充线程的属性
	ret_val = pthread_attr_init(&attr);

	if (ret_val != 0)
	{
		cout << "Pthread_attr_init error!" << endl;
		exit(1);
	}
	else
	{
		cout << "pthread_attr_init done!" << endl;
	}
	//其中pthread_attr_setdetachstate()函数把线程设置为PTHREAD_CREATE_DETACHED，这时，被创建的线程不需要等待主线程等待创建的
	//线程结束
	ret_val = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	if (ret_val != 0)
	{
		cout << "Pthread_attr_setdetachstate error!" << endl;
		exit(1);
	}
	else
	{
		cout << "pthread_attr_setdetachestate done" << endl;
	}

	//设置线程调度方式是轮转法
	ret_val = pthread_attr_setschedpolicy(&attr, SCHED_RR);

	if (ret_val != 0)
	{
		cout << "Pthread_attr_setschedpolicy error!" << endl;
		exit(1);
	}
	else
	{
		cout << "pthread_attr_setschedpolicy done!" << endl;
	}

	//设置线程优先级为2,默认为0
	ret_val = pthread_attr_setschedparam(&attr, &sp);
	//
	if (ret_val != 0)
	{
		cout << "Pthread_attr_setschedparam error!" << endl;
		exit(1);
	}
	else
	{
		cout << "pthread_attr_setschedparam done!" << endl;
	}

	//
	ret_val = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);

	if (ret_val != 0)
	{
		cout << "Pthread_attr_setinheritsched error!" << endl;
		exit(1);
	}
	else
	{
		cout << "pthread_attr_setinheritsched done!" << endl;
	}

	ret_val = pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
	if (ret_val != 0)
	{
		cout << "Pthread_attr_setscope error!" << endl;
		exit(1);
	}
	else
	{
		cout << "pthread_attr_setscope done!" << endl;
	}

	//释放线程对象
	ret_val = pthread_attr_destroy(&attr);
	if (ret_val)
	{
		cout << "Pthread_attr_destroy error!" << endl;
		exit(1);
	}
	else
	{
		cout << "pthread_attr_destroy done!" << endl;
	}

	cout << "now sleep 5 secs" << endl;
	sleep(5);

	return 0;
}
