#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int main()
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char ch = 'A';

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("192.168.3.88");
    address.sin_port = htons(9374);
    len = sizeof(address);

    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1)
    {
        perror("oops: client");
        exit(1);
    }
    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    cout<<"char from server = "<<ch<<endl;
    close(sockfd);
    
    return 0;
}
