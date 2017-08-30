//============================================================================
// Name        : shared-memory.cpp
// Author      : Leo.C.Wu
// Version     :
// Copyright   : Leo.C.Wu@NavyBlue
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sys/shm.h>
#include <unistd.h>
#include <cstdio>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string>
using namespace std;

typedef struct
{
    char name[4];
    int age;
} people;

int main(int argc, char** argv) // map a normal file as shared mem:

{
    int fd,i;
    people *p_map;
    char temp;

    string shared_memory("/tmp/shared_memory");
    fd=open(shared_memory.c_str(), O_CREAT|O_RDWR|O_TRUNC, 00777);

    lseek(fd,sizeof(people)*5-1,SEEK_SET);
    write(fd,"",1);
    //内存映射
    p_map = (people*) mmap( NULL,sizeof(people)*10,PROT_READ|PROT_WRITE,
            MAP_SHARED,fd,0 );
    close( fd );
    temp = 'a';
    for(i=0; i<10; i++)
    {
        temp += 1;
        (*(p_map + i)).name[0] = temp;
        (*(p_map + i)).name[1] = '\0';
        (*(p_map + i)).age = 20 + i;
    }
    printf("initialize over \n ");
    sleep(10);
    munmap( p_map, sizeof(people)*10 );
    printf( "umap ok \n" );
}
