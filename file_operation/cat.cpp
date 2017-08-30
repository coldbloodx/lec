//system headers
#include <unistd.h>

//C++ headers
#include <cstdio>

int main()
{
    //while there is data on standard in (fd, 0), copy it to standard
    //out (fd, 1). exit one no more data is available.
    char buf[1024];
    int len;

    //len will be >=0 while data is available, and read is successful
    while((len = read(STDIN_FILENO, buf, sizeof(buf))) > 0)
    {
        if(write(1, buf, len) != len)
        {
            perror("write");
            return 1;
        }
    }

    //len was <= 0; if len = 0, no more data is available.
    //otherwise, an error occured.
    if(len < 0)
    {
        perror("read");
        return 1;
    }

    return 0;
}
