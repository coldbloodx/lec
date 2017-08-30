#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <string>
#include <cstdlib>
using namespace std;

const int THREAD_NUMBER = 2;
int retval_hello1 = 2, retval_hello2 = 3;

void* hello1(void * arg)
{
	char * hello_str = (char *) arg;
	cout << hello_str << endl;
	for (int i = 0; i < 10; ++i)
	{
		sleep(1);
		cout << "thread1: " << i << endl;
	}
	cout << endl;
	pthread_exit(&retval_hello1);
}

void* hello2(void * arg)
{
	char * hello_str = (char*) arg;
	cout << hello_str << endl;
	for (int i = 0; i < 10; ++i)
	{
		sleep(1);
		cout << "thread2: " << i << endl;
	}
	cout << endl;
	pthread_exit(&retval_hello2);
}

int main()
{
	int i, ret_val;
	int * retval_hello[2];
	//声明pthread_t类型的array，用来存放创建线程得到的线程标志，这里创建的两个线程，分别传递了不同的参数
	//arg[0]和arg[1]分别指向所要传递的字符串的起始地址。

	pthread_t pt[THREAD_NUMBER];
	const char * arg[THREAD_NUMBER];

	arg[0] = "Thread1";
	arg[1] = "Thread2";
	cout << "Begin to create threads..." << endl;

	ret_val = pthread_create(&pt[0], NULL, hello1, (void *) arg[0]);
	if (ret_val != 0)
	{
		cout << "create thread error" << endl;
	}

	ret_val = pthread_create(&pt[1], NULL, hello2, (void *) arg[1]);
	if (ret_val != 0)
	{
		cout << "create thread error" << endl;
	}

	cout << "Now,the main thread returns." << endl;
	cout << "Begin to wait for threads..." << endl;
	for (int i = 0; i < 10; ++i)
	{
		sleep(1);
		cout << "main thread" << i << endl;
	}
	for (i = 0; i < THREAD_NUMBER; i++)
	{
		ret_val = pthread_join(pt[i], (void **) &retval_hello[i]);
		if (ret_val != 0)
		{
			cout << "pthread_join error" << endl;
			exit(1);
		}
		else
		{
			cout << "return value is " << *retval_hello[i] << endl;
		}
	}
	return 0;
}
