#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

//for xdr header 
#include <rpc/xdr.h>

int MAX_DATA_SIZE = 10000;
int PORT= 8080;

typedef struct {
    char stream[4];
    char* clusters;
    int   ncluster;
} data;


int main() 
{
    int sockfd, numbytes;
    char buff[MAX_DATA_SIZE];
    struct sockaddr_in their_addr;

    char buffer[1000] = {0};
    data mydata = {0};

    char* clusters = "cluster1 clsuter2 cluster3";
    char* sp = NULL;
    int ncluster = 3;
    XDR  xdr = {0};

    int rc = 0;

    mydata.stream[0] = 'a';
    mydata.stream[1] = 'b';
    mydata.stream[2] = 'c';
    mydata.stream[3] = 'd';

    mydata.ncluster = ncluster;
    mydata.clusters = clusters;

    xdrmem_create(&xdr,  buffer, sizeof(buffer), XDR_ENCODE);

    int streamlen = sizeof(mydata.stream);
    sp = (char*)&mydata.stream;
    rc = xdr_bytes(&xdr, (char**)&sp, &streamlen, streamlen);             

    if ( !rc ) {                                                              
        printf("encode stream fail\n");                                       
    }                                                                         

    rc = xdr_string(&xdr, &mydata.clusters, strlen(mydata.clusters));
    if ( !rc ) {
        printf("encode clusters fail\n");
    }

    rc = xdr_int(&xdr, &mydata.ncluster);
    if ( !rc ) {
        printf("encode nclusters fail\n");
    }


    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(PORT);
    inet_aton("192.168.2.138", &their_addr.sin_addr);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(PORT);
    inet_aton("192.168.2.138", &their_addr.sin_addr);


    if (connect(sockfd, (struct sockaddr*) &their_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("connect");
        exit(1);
    }

    if ((numbytes = recv(sockfd, buff, MAX_DATA_SIZE, 0)) == -1)
    {
        perror("receive");
        exit(1);
    }

    numbytes = send(sockfd, buffer, sizeof(buffer), 0);
    if (-1 == numbytes) {
        perror("send");
    }

    printf("received: %s\n", buff);

    close(sockfd);


    return 0;
}
