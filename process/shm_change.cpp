//============================================================================
// Name        : ex07-01-shared-memory.cpp
// Author      : Leo.C.Wu
// Version     :
// Copyright   : Leo.C.Wu@NavyBlue
// Description : Hello World in C++, Ansi-style
//============================================================================

//system libs
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

//crt libs
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
using namespace std;

int main()
{
    void *shared_memory = NULL;
    int shared_memory_id = 0;

    //create shared memory
    shared_memory_id = shmget((key_t)4321, 512, 0666 | IPC_CREAT);
    if(-1 == shared_memory_id)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    cout<<shared_memory_id<<endl;
    //map shared memory to our process
    shared_memory = shmat(shared_memory_id, NULL, 0);
    if((void*)-1 == shared_memory)
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    cout<<"Shared memory attached at:"<<shared_memory<<endl;
    char* buff = (char*)shared_memory;
    cout<<buff<<endl;

    strcpy((char*)shared_memory, "got the memory contents!");

    //detach memory from our process
    if(-1 == shmdt(shared_memory))
    {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);

    return 0;
}
