#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    char s[]="Hello World!";  
    int Uppercase = 0; //modified by the lambda  
    for_each(s, s+sizeof(s), [&Uppercase] (char c) 
    {  
        if (isupper(c))  
             Uppercase++;  
    });  
    cout<< Uppercase<<" uppercase letters in: "<< s<<endl;  
    return 0;
}
