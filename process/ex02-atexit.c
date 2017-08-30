#include <stdio.h>

void clean1()
{
    printf("in clean1\n");
}

void clean2()
{
    printf("in clean2\n");
}

int main()
{
    if(atexit(clean2) != 0)
    {
        perror("can not add clean2");
    }
    if(atexit(clean1) != 0)
    {
        perror("can not add clean1 - 1");
    }
    if(atexit(clean1) != 0)
    {
        perror("can not add clean1 - 2");
    }
    printf("last line in main\n");
    return 0;
}



