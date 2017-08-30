#include <iostream>
using namespace std;

void fun(int int_param = 0)
{
    cout<<"in int"<<endl;
    cout<<int_param<<endl;
}

void fun(char* charparm = "null ptr")
{
    cout<<"in char"<<endl;
    cout<<charparm<<endl;
}

int main()
{
    fun(10);
    fun("test string");
    //fun();
    fun(0);
    //following grammar will be support in the future
    //fun(nullptr);
    return 0;
}
