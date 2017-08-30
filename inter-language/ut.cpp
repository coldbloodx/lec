#include <iostream>
#include "operation.h"
using namespace std;

int main()
{
    Operation op;
    cout<<"1 + 1 = " << op.add<int>(1, 1) <<endl;
    cout<<"1 - 1 = " << op.sub<int>(1, 1) <<endl;
    cout<<"1 X 1 = " << op.mul<int>(1, 1) <<endl;
    cout<<"1 / 1 = " << op.div<int>(1, 1) <<endl;

    return 0;
}
