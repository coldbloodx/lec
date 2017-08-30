//system libs
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//c++ libs
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string.h>
using namespace std;

const int PORT = 3490;
const int BACKLOG = 5;

int main()
{
    int sockfd, newfd;

    //create two sockaddr_in vars
    struct sockaddr_in myAddr;
    struct sockaddr_in theirAddr;
    int sinSize;

    //init vars
    myAddr.sin_family = AF_INET;
    myAddr.sin_port = htons(PORT);
    myAddr.sin_addr.s_addr = INADDR_ANY;
    memset(&myAddr.sin_zero, 0, sizeof(myAddr.sin_zero));

    if (-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
    {
        perror("socket");
        exit(1);
    }

    if (-1 == bind(sockfd, (struct sockaddr*) &myAddr, sizeof(struct sockaddr)))
    {
        perror("bind");
        exit(1);
    }

    if (-1 == listen(sockfd, BACKLOG))
    {
        perror("listen");
        exit(1);
    }

    int con_count = 1;
    while (1)
    {
        sinSize = sizeof(struct sockaddr_in);
        if (-1 == (newfd = accept(sockfd, (struct sockaddr *) &theirAddr,
                        (socklen_t*) &sinSize)))
        {
            perror("accept");
            continue;
        }
        cout << "server: got the " << con_count << " connection from "
            << inet_ntoa(theirAddr.sin_addr) << endl;

        char buff[256];
        memset(buff, 0, sizeof(buff));
        sprintf(buff, "hello, you are the %d guest...", con_count);

        if (send(newfd, buff, sizeof(buff), 0) == -1)
        {
            perror("send");
        }
        close(newfd);
        ++con_count;
    }
    return 0;
}

