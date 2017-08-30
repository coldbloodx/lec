//system headers
#include <sys/types.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

//c++ headers
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int main()
{
    char buffer[128];
    int result, nread;
    fd_set inputs, testfds;
    struct timeval timeout;

    FD_ZERO(&inputs);
    FD_SET(0, &inputs);

    while(1)
    {
        testfds = inputs;
        timeout.tv_sec = 2;
        timeout.tv_usec = 50000;

        //result = select(FD_SETSIZE, &testfds, (fd_set *)NULL, (fd_set *)NULL, &timeout);
        result = select(FD_SETSIZE, &testfds, (fd_set *)NULL, (fd_set *)NULL, NULL);
        switch(result)
        {
            case 0:
                cerr<<"time out"<<endl;
                break;
            case -1:
                perror("select");
                exit(1);
            default:
                if(FD_ISSET(0, &testfds))
                {
                    ioctl(0, FIONREAD, &nread);
                    if(nread == 0)
                    {
                        cout<<"keyboard done"<<endl;
                        exit(0);
                    }
                    nread = read(0, buffer, nread);
                    buffer[nread] = 0;
                    cout<<"read "<<nread<<" from keyboard:"<<buffer<<endl;
                }
                break;
        }
    }

    return 0;
}
