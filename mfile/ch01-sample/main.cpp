//testing make file
//entry for the whole program

#include <iostream>
#include "addition.h"
#include "subtraction.h"
#include "multiplication.h"
#include "division.h"

using namespace std;


double minus(double a, double b)
{
    return a - b;
}

int main()
{
    cout<<"test"<<endl;
    cout<<"1 + 1 = "<<add(1, 1)<<endl;
    cout<<"2 - 1 = "<<subtract(2, 1)<<endl;
    cout<<"2 x 3 = "<<multiplicate(2, 3)<<endl;
    cout<<"4 / 3 = "<<divide(4, 3)<<endl;
    cout<<::minus(5, 1)<<endl;
    return 0;
}


