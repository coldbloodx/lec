#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
using namespace std;

class InitTest 
{
public:
    InitTest (int int_param, char char_param);
    virtual ~InitTest ();
    void output();
private:
    /* data */
    int int_member;
    char char_member;
    int int_array[5];
    double double_array[2];
};

InitTest::InitTest(int int_param,char char_param):
    int_member(int_param), char_member(char_param),
    int_array{1, 2, 3, 4, 5},
    double_array{1.0, 2.0}
{

}

InitTest::~InitTest()
{
}

void InitTest::output()
{
    cout<<"int_member:"<<int_member<<endl
        <<"char_member:"<<char_member<<endl;
    cout<<"int_array:";
    copy(int_array, int_array+sizeof(int_array)/sizeof(int), 
        ostream_iterator<int>(cout, " "));
    cout<<endl;
    cout<<"double_array:";
    copy(double_array, double_array + sizeof(double_array)/sizeof(double),
        ostream_iterator<double>(cout, " "));
}

int main()
{
    vector<string> string_vector = {"one", "two", "three", "four"};
    auto bi = string_vector.begin(), ei = string_vector.end();
    copy(bi, ei, ostream_iterator<string>(cout, " "));
    cout<<endl;

    InitTest init_test = {1, 'c'};
    init_test.output();
    cout<<endl;

    int* pint = new int[3] {1, 2, 3};
    cout<<"pint:";
    copy(pint, pint+3, ostream_iterator<int>(cout, " "));
    cout<<endl;

    return 0;
}
