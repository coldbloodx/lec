#include <stdio.h>

extern int add_int(int lhs, int rhs);
extern int sub_int(int lhs, int rhs);
extern int mul_int(int lhs, int rhs);
extern int div_int(int lhs, int rhs);

int main()
{
    printf("1 + 1 = %d\n", add_int(1, 1));
    printf("1 - 1 = %d\n", sub_int(1, 1));
    printf("1 * 1 = %d\n", mul_int(1, 1));
    printf("1 / 1 = %d\n", div_int(1, 1));
    return 0;
}
