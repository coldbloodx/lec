#include <stdio.h>         
#include <string.h>          
#include <unistd.h>       
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <stdlib.h>

#define PORT 1234           //服务器端口
#define BACKLOG 5           //listen队列中等待的连接数
#define MAXDATASIZE 1024 //缓冲区大小

typedef struct _CLIENT
{        
    //客户端结构体
    int       fd;        //客户端socket描述符
    char*  name;
    struct sockaddr_in addr;     //客户端地址信息结构体
    char* data;                                       
} CLIENT; 

void process_cli(CLIENT *client, char* recvbuf, int len);  //客户请求处理函数
void savedata(char* recvbuf, int len, char* data);

int main()
{
    int    i, maxi, maxfd,sockfd;
    int    nready;
    ssize_t      n;
    fd_set      rset, allset;    //select所需的文件描述符集合
    int listenfd, connectfd;     //socket文件描述符
    struct sockaddr_in server;     //服务器地址信息结构体

    CLIENT client[FD_SETSIZE];     //FD_SETSIZE为select函数支持的最大描述符个数
    char recvbuf[MAXDATASIZE];    //缓冲区
    int sin_size;            //地址信息结构体大小

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
    {    
        //调用socket创建用于监听客户端的socket
        perror("Creating socket failed.");
        exit(1);
    }

    int opt = SO_REUSEADDR;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));    //设置socket属性

    bzero(&server,sizeof(server));
    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);
    server.sin_addr.s_addr = htonl (INADDR_ANY);

    if (bind(listenfd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1) 
    {    
        //调用bind绑定地址
        perror("Bind error.");
        exit(1);
    }   

    if(listen(listenfd,BACKLOG) == -1)
    {      
        //调用listen开始监听
        perror("listen() error\n");
        exit(1);
    }

    sin_size=sizeof(struct sockaddr_in);
    //初始化select
    maxfd = listenfd;     
    maxi = -1;               
    for (i = 0; i < FD_SETSIZE; i++) 
    {
        client[i].fd = -1;  
    }
    FD_ZERO(&allset);        //清空
    FD_SET(listenfd, &allset);    //将监听socket加入select检测的描述符集合

    while(1)
    {
        struct sockaddr_in addr;
        rset = allset;            
        nready = select(maxfd+1, &rset, NULL, NULL, NULL);    //调用select
        printf("select saw rset actions and the readfset num is %d. \n",nready );

        if (FD_ISSET(listenfd, &rset)) 
        {      //检测是否有新客户端请求
            printf("accept a connection.\n");
            //调用accept，返回服务器与客户端连接的socket描述符
            if((connectfd = accept(listenfd,(struct sockaddr *)&addr,(socklen_t *)&sin_size))==-1) 
            {
                perror("accept() error\n");
                continue;
            }
            //将新客户端的加入数组
            for (i = 0; i < FD_SETSIZE; i++)
            {
                if (client[i].fd < 0) 
                {
                    client[i].fd = connectfd;    //保存客户端描述符
                    client[i].name = new char[MAXDATASIZE];
                    client[i].addr = addr;
                    client[i].data = new char[MAXDATASIZE];
                    client[i].name[0] = '\0';
                    client[i].data[0] = '\0';
                    printf("You got a connection from %s.  ",inet_ntoa(client[i].addr.sin_addr) );
                    break;
                }
            }    

            printf("add new connect fd.\n");
            if (i == FD_SETSIZE)          
                printf("too many clients\n");
            FD_SET(connectfd, &allset);   //将新socket连接放入select监听集合
            if (connectfd > maxfd)  
                maxfd = connectfd;   //确认maxfd是最大描述符
            if (i > maxi)          //数组最大元素值
                maxi = i;          
            if (--nready <= 0) 
                continue;      //如果没有新客户端连接，继续循环
        }

        for (i = 0; i <= maxi; i++) 
        {     
            if ( (sockfd = client[i].fd) < 0)       //如果客户端描述符小于0，则没有客户端连接，检测下一个
                continue; 

            if (FD_ISSET(sockfd, &rset)) 
            {        
                //检测此客户端socket是否有数据    
                printf("recv occured for connect fd[%d].\n",i);
                if ( (n = recv(sockfd, recvbuf, MAXDATASIZE,0)) == 0) 
                { 
                    //从客户端socket读数据，等于0表示网络中断
                    close(sockfd);        //关闭socket连接
                    printf("Client( %s ) closed connection. User's data: %s\n",client[i].name,client[i].data);
                    FD_CLR(sockfd, &allset);    //从监听集合中删除此socket连接
                    client[i].fd = -1;        //数组元素设初始值，表示没客户端连接
                    delete client[i].name;
                    delete client[i].data;
                } else
                    process_cli(&client[i], recvbuf, n);    //接收到客户数据，开始处理
                if (--nready <= 0)     
                    break;       //如果没有新客户端有数据，跳出for循环回到while循环
            }
        }
    }
    close(listenfd);  //关闭服务器监听socket     
}

void process_cli(CLIENT *client, char* recvbuf, int len)
{
    char sendbuf[MAXDATASIZE];

    recvbuf[len-1] = '\0';
    if (strlen(client->name) == 0) 
    {
        memcpy(client->name,recvbuf, len);
        printf("Client's name is %s.\n",client->name);
        return;
    }

    printf("Received client( %s ) message: %s\n",client->name, recvbuf);
    savedata(recvbuf,len, client->data);
    for (int i1 = 0; i1 < len - 1; i1++) 
    {
        sendbuf[i1] = recvbuf[len - i1 -2];
    }
    sendbuf[len - 1] = '\0';

    send(client->fd,sendbuf,strlen(sendbuf),0);
}

void savedata(char* recvbuf, int len, char* data)
{
    int start = strlen(data);
    for (int i = 0; i < len; i++) 
    {
        data[start + i] = recvbuf[i];
    }        
}
