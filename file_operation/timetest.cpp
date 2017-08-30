//============================================================================
// Name        : ch01-ex03-time-consuming-test.cpp
// Author      : Leo.C.Wu
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>

#include <time.h>

#include <unistd.h>//for read, write
#include <fcntl.h>//for open
#include <sys/types.h>//for open
#include <sys/stat.h>//for open
using namespace std;

const string FILE_NAME("cs.xml");

void crt_operate_file()
{
    ifstream in_file(FILE_NAME.c_str());
    string line;

    while (!in_file.eof())
    {
        in_file >> line;
        if (!in_file.eof())
        {
            //cout << line;
        }
    }
}

void sc_operate_file()
{
    char buffer[256];
    int fd_in = 0, fd_out = 0;
    fd_in = open(FILE_NAME.c_str(), O_RDONLY);
    while (read(fd_in, buffer, sizeof(buffer)) > 0)
    {
        //cout<<buffer<<endl;
    }
    close(fd_in);
}

int main()
{
    clock_t cbegin, cend, sbegin, send;
    cbegin = clock();
    cout << "crt read file begin:" << endl;
    for (int i = 0; i < 10000; ++i)
        crt_operate_file();
    cout << "crt read file end." << endl;
    cend = clock();

    sbegin = clock();
    cout << "system call read file begin:" << endl;
    for (int i = 0; i < 10000; ++i)
        sc_operate_file();
    cout << "system call read file end." << endl;
    send = clock();

    double crt_cost = (double) (cend - cbegin) / CLOCKS_PER_SEC;
    double sc_cost = (double) (send - sbegin) / CLOCKS_PER_SEC;
    cout << "CRT cost:" << crt_cost << endl;
    cout << "System Call cost:" << sc_cost << endl;

    return 0;
}
