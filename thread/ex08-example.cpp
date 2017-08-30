//============================================================================
// Name        : ex08-example.cpp
// Author      : Leo.C.Wu@NavyBlue
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <string>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <cstdlib>
#include <cstdio>
using namespace std;

const int BUFFER_SIZE = 1024;
const int MAX_FILE_NUM = 10;

struct file
{
	char * fileName;
	char * host;
	int fd;
	int doneFlags;
	pthread_t tid;
};

file aFile[MAX_FILE_NUM];

//GET_CMD is the HTTP request threads sent to server
#define GET_CMD "GET %s HTTP/1.1\r\nhost:%s\r\n\r\n"

pthread_mutex_t nDoneMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t nDoneCond =PTHREAD_COND_INITIALIZER;

void* saveFile(void * ptr);


int sentCmd(file * fptr)
{
	int nSend;
	char * ptr;
	int nLeft,n;
	char buffer[BUFFER_SIZE];
	n = snprintf(buffer,sizeof(buffer),GET_CMD,fptr->fileName,fptr->host);
	ptr = buffer;
	nLeft  = n;

//send the http request with while loop
	while (nLeft > 0)
	{
		nSend = send(fptr->fd,ptr,nLeft,0);
		if (nSend <= 0)
		{
			return -1;
		}
		nLeft -= nSend;
		ptr += nSend;
	}
	return nSend;
}

int tcp_connect(const char * host,const char * port)
{
	int sockfd;
	int connReturnValue;
	sockaddr_in serverAddr;
	hostent *aHostent;
	//char * p = NULL;

	//get address information
	aHostent = gethostbyname(host);
	if (aHostent == NULL)
	{
		cerr<<"get host name error"<<endl;
		return -1;
	}

	//create tcp socket
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if (sockfd == -1)
	{
		cerr<<"create socket error"<<endl;
		return -1;
	}

    //initialize the data structure
    bzero(&serverAddr,sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(port));
    mempcpy((void *)&serverAddr.sin_addr,aHostent->h_addr,sizeof(in_addr));
    connReturnValue = connect(sockfd,(sockaddr*)&serverAddr,sizeof(serverAddr));
    if (connReturnValue == -1)
    {
    	cerr<<"connect error"<<endl;
    	return -1;
    }
    return sockfd;
}

void* saveFile(void * ptr)
{
    int fd,n;
    int returnValue;
    char buffer[BUFFER_SIZE];
    file * fptr;
    int fileFD;
    char * p;
    fptr = (file*)ptr;
    int i;

    fd = tcp_connect(fptr->host,"80");
    if (fd < 0)
    {
    	cerr<<"tcp connect error"<<endl;
    	pthread_exit(NULL);
    }
    fptr->fd = fd;
    cout<<"begin save file:"<<fptr->fileName<<","<<fd<<","<<fptr->tid<<endl;
    returnValue = sentCmd(fptr);
    if (returnValue < 0)
    {
    	cout<<"sendCmd error"<<endl;
    	pthread_exit(NULL);
    }
    //replace '/' with '-' in file
    p = fptr->fileName;
    for (i = 0;  (*p) != '\0' ;i++ )
    {
    	if (fptr->fileName[i] == '/')
    	{
    		fptr->fileName[i] = '_';
    	}
    	p++;
    }

    fileFD = open(fptr->fileName,O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
    if (fd == -1)
    {
    	cerr<<"open file error"<<endl;
    	pthread_exit(NULL);
    }

    for (; ; )
    {
    	n = read(fd,buffer,BUFFER_SIZE);
    	if (n <=0)
    	{
    		break;
    	}
    	int x = write(fileFD,buffer,n);
    	if(x<0)
    	{
    		cerr<<"write error"<<endl;
    	}
    }
    cout<<fptr->fileName<<"is downloaded"<<endl;

    close(fd);
    close(fileFD);
    fptr->doneFlags = 1;
    pthread_mutex_lock(&nDoneMutex);
    pthread_cond_signal(&nDoneCond);
    pthread_mutex_unlock(&nDoneMutex);
    pthread_exit(NULL);
}

int main(int argc, char** argv)
{
    int i;
    int fileNum;
    int leftFileNum;
    pthread_t tid;
    //file * fptr;

    //host is the target site,one file at least should be downloaded
    if (argc < 3)
    {
    	cout<<"usage:web file <host> file1 file2.."<<endl;
    	exit(1);
    }
    fileNum = argc - 2;
    leftFileNum = fileNum;

    for (i = 0;i<fileNum ;i++ )
    {
    	aFile[i].fileName = argv[i+2];
    	aFile[i].host = argv[1];
    	aFile[i].doneFlags = 0;
    }

    //create threads
    for (i = 0 ; i < fileNum ; i++ )
    {
    	int returnValue = pthread_create(&tid,NULL,saveFile,&aFile[i]);
    	if ( returnValue < 0)
    	{
    		cout<<"pthread create error!"<<endl;
    		exit(1);
    	}
    	aFile[i].tid = tid;
    }

    while (leftFileNum > 0)
    {
        pthread_mutex_lock(&nDoneMutex);
        pthread_cond_wait(&nDoneCond,&nDoneMutex);
        for (i = 0; i<fileNum ; i++ )
        {
        	if (aFile[i].doneFlags == 1)
        	{
        		pthread_join(aFile[i].tid,NULL);
        	}
        }
        pthread_mutex_unlock(&nDoneMutex);
        leftFileNum--;
    }
    exit(0);
}
