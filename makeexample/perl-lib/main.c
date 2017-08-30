#include <stdio.h>
#include <stdlib.h>

#include "lib/libop.h"


int main()
{
    printf(" 1 + 1 = %f\n", xadd(1, 1));
    printf(" 1 - 1 = %f\n", xsub(1, 1));
    printf(" 1 * 1 = %f\n", xmul(1, 1));
    printf(" 1 / 1 = %f\n", xdiv(1, 1));
    return 0;
}


