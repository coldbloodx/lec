//system libs
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netdb.h>
//c++ libs
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string.h>
using namespace std;

const int PORT = 3490;
const int MAX_DATA_SIZE = 100;

int main(int argc, char* argv[])
{
    int sockfd, numbytes;
    char buff[MAX_DATA_SIZE];
    struct hostent *he;
    struct sockaddr_in their_addr;

    if (argc <= 2)
    {
        he = gethostbyname("localhost");
        if(NULL == he)
        {
            perror("gethostbyname");
            exit(1);
        }
    }
    else
    {
        he = gethostbyname(argv[1]);
        if(he == NULL)
        {
            perror("gethostbyname");
            exit(1);
        }
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(PORT);
    their_addr.sin_addr = *((struct in_addr*) he->h_addr);
    bzero(&their_addr.sin_zero, sizeof(their_addr.sin_zero));

    if (connect(sockfd, (sockaddr*) &their_addr, sizeof(sockaddr)) == -1)
    {
        perror("connect");
        exit(1);
    }

    if ((numbytes = recv(sockfd, buff, MAX_DATA_SIZE, 0)) == -1)
    {
        perror("receive");
        exit(1);
    }
    cout<<buff<<endl;

    close(sockfd);
    return 0;
}
