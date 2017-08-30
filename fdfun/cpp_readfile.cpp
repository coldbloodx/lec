//============================================================================
// Name        : ch01-ex02-runtime-file-operation.cpp
// Author      : Leo.C.Wu
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>

using namespace std;

const string IN_FILE = "cs.xml";
const string OUT_FILE = "cs_out.xml";

void read_file()
{
    ifstream in_file(IN_FILE.c_str());
    //read file with stream operator
    string word;
    cout << "read file word by word via ifstream>>:" << endl;
    vector<int> intvector;
    int i = 1;
    while (!in_file.eof())
    {
        in_file >> word;

        if (!in_file.eof())
        {
            cout << " " << word ;
        }
    }

    in_file.close();
    //read file line by line with member function string::getline() --> it's a static member.
    cout << endl << "read file line by line via string::getline" << endl;
    in_file.open(IN_FILE.c_str());
    i = 1;
    while (getline(in_file, word))
    {
        cout << "line count" << i << ":" << word << endl;
        ++i;
    }
    in_file.close();
}

void write_file()
{
    vector<int> int_vector;
    for (int i = 0; i < 100; ++i)
    {
        int_vector.push_back(i);
    }
    ofstream out_file(OUT_FILE.c_str());
    copy(int_vector.begin(), int_vector.end(),
            ostream_iterator<int> (out_file, "\n"));
}

int main()
{
    read_file();
    write_file();
    return 0;
}
