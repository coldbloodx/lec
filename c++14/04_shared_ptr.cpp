//============================================================================
// Name        : shared-ptr.cpp
// Author      : Leo.C.Wu
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <tr1/memory>
#include <tr1/shared_ptr.h>
using namespace std;

int main()
{
	shared_ptr<int> pint(new int(100));
	cout<<*pint<<endl;
	return 0;
}
