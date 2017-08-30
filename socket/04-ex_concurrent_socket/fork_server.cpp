//system libs
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <netinet/in.h>
//c++ libs
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string.h>
using namespace std;

const int BACK_LOG = 20;

int main()
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    int result;
    fd_set readfds, testfds;

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(9374);
    server_len = sizeof(server_address);

    bind(server_sockfd, (sockaddr *)&server_address, server_len);

    listen(server_sockfd, BACK_LOG);

    FD_ZERO(&readfds);
    FD_SET(server_sockfd, &readfds);

    while(1)
    {
        char ch;
        int nread;
        testfds = readfds;

        cout<<"server waiting"<<endl;
        
        int new_fd = accept(server_sockfd, (sockaddr*)&client_address,
                (socklen_t*)&client_len);

        if(fork() == 0)
        {
            char buff[256];
            memset(buff, 0, sizeof(buff));
            read(new_fd, &ch, 1);
            cout<<"got char from client:"<<ch<<endl;
            write(new_fd, &ch, 1);
            cout<<"write char to client:"<<ch<<endl;
            exit(0);
        }

    }

    return 0;
}
