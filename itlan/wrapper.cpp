#include "operation.h"

extern "C"
{
    int add_int(int lhs, int rhs)
    {
        Operation op;
        return op.add<int>(lhs, rhs); 
    }

    int sub_int(int lhs, int rhs)
    {
        Operation op;
        return op.sub<int>(lhs, rhs);
    }

    int mul_int(int lhs, int rhs)
    {
        Operation op;
        return op.mul<int>(lhs, rhs);
    }

    int div_int(int lhs, int rhs)
    {
        Operation op;
        return op.div<int>(lhs, rhs);
    }
};
