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
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    int sinSize;

    //init vars
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&my_addr.sin_zero, 0, sizeof(my_addr.sin_zero));

    //create server socket
    if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        perror("socket");
        exit(1);
    }

    //name server socket
    if (-1 == bind(sockfd, (struct sockaddr*) &my_addr, sizeof(struct sockaddr)))
    {
        perror("bind");
        exit(1);
    }

    //make var to remeber connect count
    int connect_count = 0;
    //event loop
    while(1)
    {
        char buffer[256];
        memset(buffer, 0, sizeof(buffer));
        socklen_t socklen = sizeof(their_addr);

        //receive remote connect 
        //here their is a return parameter to record the client address
        int receive_len = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                (sockaddr*)&their_addr, &socklen);
        buffer[receive_len] = '\0';

        //make an echo message to client
        cout<<"receive "<<receive_len<<" bytes from "<<inet_ntoa(their_addr.sin_addr)<<"."
            <<"the content is:"<<buffer<<endl;
        char message[256];
        memset(message, sizeof(message), 0);
        sprintf(message, "you are %d guest to localhost", connect_count);

        //send message to client address
        if (sendto(sockfd, message, sizeof(message), 0, (struct sockaddr*)&their_addr, sizeof(their_addr)) == -1)
        {
            perror("sendto");
        }

        ++connect_count;
    }

    return 0;
}

