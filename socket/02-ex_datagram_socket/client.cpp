//system libs
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//c++ libs
#include <string.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

const int MAXLINE = 80;
const int SERV_PORT = 8888;

void do_cli(FILE *fp, int sockfd, struct sockaddr *pservaddr, socklen_t servlen)
{
    int n;
    char sendline[MAXLINE], recvline[MAXLINE + 1];

    /* connect to server */
    if(connect(sockfd, (struct sockaddr *)pservaddr, servlen) == -1)
    {
        perror("connect error");
        exit(1);
    }

    while(fgets(sendline, MAXLINE, fp) != NULL)
    {
        /* read a line and send to server */
        write(sockfd, sendline, strlen(sendline));
        /* receive data from server */
        n = read(sockfd, recvline, MAXLINE);
        if(n == -1)
        {
            perror("read error");
            exit(1);
        }
        recvline[n] = 0; /* terminate string */
        cout<<"get message from server:"<<recvline<<endl;
    }
}

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;

    /* check args */

    /* init servaddr */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    char* testaddr = "127.0.0.1";
    if(argc < 2)
    {
        cout<<"make 127.0.0.1 as default server address"<<endl;
    }
    else
    {
        testaddr = argv[1];
    }
    if(inet_pton(AF_INET, testaddr, &servaddr.sin_addr) <= 0)
    {
        printf("[%s] is not a valid IPaddress\n", argv[1]);
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    do_cli(stdin, sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    return 0;
}
