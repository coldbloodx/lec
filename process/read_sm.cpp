//============================================================================
// Name        : share-memory-read.cpp
// Author      : Leo.C.Wu
// Version     :
// Copyright   : Leo.C.Wu@NavyBlue
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <string>
using namespace std;

typedef struct
{
    char name[4];
    int age;
} people;

int main(int argc, char** argv) // map a normal file as shared mem:
{
    int fd, i;
    people *p_map;

    string shared_memory("/tmp/shared_memory");
    fd=open( shared_memory.c_str(), O_CREAT|O_RDWR, 00777 );
    p_map = (people*) mmap(NULL, sizeof(people) * 10, PROT_READ | PROT_WRITE,
            MAP_SHARED, fd, 0);
    for (i = 0; i < 10; i++)
    {
        printf("name: %s age %d;\n", (*(p_map + i)).name, (*(p_map + i)).age);
    }
    munmap(p_map, sizeof(people) * 10);
}
