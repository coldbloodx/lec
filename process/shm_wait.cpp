//============================================================================
// Name        : shared-memory.cpp
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
#include <string.h>
#include <cstdio>
#include <cstdlib>
using namespace std;

int main()
{
    void *shared_memory = NULL;
    int shared_memory_id = 0;
    char buff[512];
    memset(buff, 0, (sizeof(buff)));
    strcpy(buff, "this is a test");
    cout<<buff<<endl;

    //create shared memory
    shared_memory_id = shmget((key_t)4321, sizeof(buff), 0666 | IPC_CREAT);
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

    memcpy(shared_memory, (void*)buff, sizeof(buff));

    //check flag whether the communication is processed
    for (int i = 0; i < 10; ++i)
    {
        cout<<"loop "<<i + 1<<endl;
        cout<<(char*)shared_memory<<endl<<endl;
        sleep(10);
    }

    //detach memory from our process
    if(-1 == shmdt(shared_memory))
    {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    if(-1 == shmctl(shared_memory_id, IPC_RMID, 0))
    {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);

    return 0;
}
