//============================================================================
// Name        : shared-ptr.cpp
// Author      : Leo.C.Wu
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

//begin for shared_ptr
#include <tr1/memory>
#include <tr1/shared_ptr.h>
//end for shared_ptr
#include <iostream>

using namespace std;
using namespace std;
using std::tr1::shared_ptr;

int main()
{
	shared_ptr<int> pint(new int(100));
	cout<<*pint<<endl;
	return 0;
}
