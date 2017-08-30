//============================================================================
// Name        : ch01-ex01-system-call.cpp
// Author      : Leo.C.Wu
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//run time header
#include <string>
#include <iostream>
#include <cstdio>
#include <string.h> //for memset
using namespace std;

//system header
#include <unistd.h>//for read, write
#include <fcntl.h>//for open
#include <sys/types.h>//for open
#include <sys/stat.h>//for open

//user header


const int BUFFER_SIZE = 256;
const string IN_FILE("infile.txt");
const string OUT_FILE("outfile.txt");

int main()
{
    //file descriptor test, 1 stands for stdout, 2 stands for stderrout.
    string word("simple test\n");
    string error_data("some test wrong data.\n");
    //extern ssize_t write (int __fd, __const void *__buf, size_t __n) __wur;
    cout<<"write some string to stdout, fd = 1:"<<endl;
    write(1, word.c_str(), word.length());
    cout<<"write some string to stderr, fd = 2:"<<endl;
    write(2, error_data.c_str(), error_data.length());

    //extern ssize_t read (int __fd, void *__buf, size_t __nbytes) __wur;
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    cout<<buffer<<endl;

    cout<<"read input from std in, fd = 0"<<endl;
    read(0, buffer, BUFFER_SIZE);
    cout<<buffer<<endl;
    cerr<<buffer<<endl;
    memset(buffer, 0, BUFFER_SIZE);

    //extern int __REDIRECT (open, (__const char *__file, int __oflag, ...), open64)
    //__nonnull ((1));
    int fd_in = 0, fd_out = 0;
    cout<<"read 10 bytes from file:"<<IN_FILE<<endl;
    fd_in = open(IN_FILE.c_str(), O_RDONLY);
    read(fd_in, buffer, 10);
    close(fd_in);
    cout<<buffer<<endl;

    int str_len = strlen(buffer);
    fd_out = open(OUT_FILE.c_str(), O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
    if(fd_out < 0)
    {
        perror("ERROR");
    }
    cout<<"write buffer:"<<buffer<<" "<<str_len<<"bytes to file:"<<OUT_FILE<<endl;
    write(fd_out, buffer, str_len);
    close(fd_out);

    fd_out = open("this is a non-exist file", O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
    if(fd_out < 0)
    {
        perror("ERROR");
    }

    return 0;
}
