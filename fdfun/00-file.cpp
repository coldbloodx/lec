//linux headers
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

//c++ headers
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <iostream>
using namespace std;

int main()
{
    int fd = 0;

    //open the file create it if it is not there, and removing its contents if it there.
    if((fd = open("test", O_TRUNC | O_CREAT | O_WRONLY, 0644)) < 0)
    {
        perror("open");
        exit(1);
    }
    int str_len = strlen("hello world!\n");
    //check write number
    if(write(fd, "hello world!\n", str_len ) != str_len)
    {
        perror("write");
    }
    close(fd);
    return 0;
}
