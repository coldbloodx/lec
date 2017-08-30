#include <cstdio>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
using namespace std;


int main(int argc, const char** argv)
{
    char buf[1024];
    FILE* ls;
    int result;
    int i;

    strcpy(buf, "ls ");
    for(i = 0; i< argc; ++i)
    {
        strcat(buf, argv[i]);
        strcat(buf, " ");
    }
    
    ls = popen(buf, "r");
    if(!ls)
    {
        perror("ls");
        return 0;
    }

    while(fgets(buf, sizeof(buf), ls))
    {
        cout<<buf;
    }
    result = pclose(ls);

    if(!WIFEXITED(result))
    {
        return 1;
    }
    return 0;
}

