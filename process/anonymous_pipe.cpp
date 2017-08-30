//============================================================================
// Name        : anonymous-pipe.cpp
// Author      : Leo.C.Wu
// Version     :
// Copyright   : Leo.C.Wu@NavyBlue
// Description : Hello World in C++, Ansi-style
//============================================================================

//anonymous pipe
//created by pipe
#include <iostream>
#include <unistd.h>
#include <string>
using namespace std;

const int INPUT = 0;
const int OUTPUT = 1;

int main()
{
    int fork_ret_val = 0;
    //create file descriptors here
    int file_descriptor_array[2] = {0,0};
    pipe(file_descriptor_array);
    //create new process with fork

    fork_ret_val = fork();
    string pipe_string("test input");
    if(0 == fork_ret_val)
    {
        //child process do its jobs here
        //close one side of pipe, write from another side
        close(file_descriptor_array[INPUT]);

        write(file_descriptor_array[OUTPUT], pipe_string.c_str(), pipe_string.length());
    }
    else
    {
        //parent process go on its jobs here
        //out child pid and parent pid
        close(file_descriptor_array[OUTPUT]);
        char buff[256];
        buff[255] = '\0';
        //read pipe data
        int read_count = read(file_descriptor_array[INPUT], buff, sizeof(buff));
        buff[read_count] = '\0';
//        int child_pid = fork_ret_val;
//        cout<<"child pid:"<<child_pid<<endl;
//        int parent_pid = getpid();
//        cout<<"parent pid:"<<parent_pid<<endl;
        cout<<"data from pipe:"<<buff<<endl;
    }
    return 0;
}
