#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/wait.h>
using namespace std;

int main()
{
    int result = system("exec ls -l *.cpp");
    if(!WIFEXITED(result))
    {
        cerr<<"abnormal exit"<<endl;
        perror("ls");
        exit(1);
    }
    exit(0);
}
