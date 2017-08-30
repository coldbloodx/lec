//system libs
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
//c++ libs
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <string.h>
using namespace std;

const int PORT = 3490;
const int MAX_DATA_SIZE = 100;

int main(int argc, char* argv[])
{
    int sockfd, numbytes;
    std::string buff("this is a test");
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

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(PORT);
    their_addr.sin_addr = *((struct in_addr*) he->h_addr);
    bzero(&their_addr.sin_zero, sizeof(their_addr.sin_zero));
    int addrlen = sizeof(their_addr);
    

    if((numbytes = sendto(sockfd, buff.c_str(), buff.size(), 0, (struct sockaddr*)(&their_addr), addrlen)) == -1)
    {
        perror("sendto");
        exit(1);
    }
    char message[256];
    memset(message, sizeof(message), 0);
    memset(&their_addr, 0, addrlen);

    if((numbytes = recvfrom(sockfd, message, sizeof(message), 0, (struct sockaddr*)(&their_addr), (socklen_t*)&addrlen)) == -1)
    {
        perror("recvfrom");
        exit(1);
    }
    cout<<"receive from server:"<<message<<endl;

    close(sockfd);
    return 0;
}
