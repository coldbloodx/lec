#include <iostream>
#include <string>
#include <cstdio>
using namespace std;


int main() 
{
    string abc("abc");
    string abd = abc;
    printf("abc addr: %x\n", abc.c_str());
    printf("abd addr: %x\n", abd.c_str());

    abd = "123";
    printf("abc addr: %x\n", abc.c_str());
    printf("abd addr: %x\n", abd.c_str());


    return 0;

}
