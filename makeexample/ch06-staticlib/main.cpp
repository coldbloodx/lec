//testing make file
//entry for the whole program

#include <iostream>

extern double add(double, double);
extern double subtract(double, double);
extern double multiplicate(double, double);
extern double divide(double, double);
using namespace std;

int main()
{
    cout<<"1 + 1 = "<<add(1, 1)<<endl;
    cout<<"2 - 1 = "<<subtract(2, 1)<<endl;
    cout<<"2 x 3 = "<<multiplicate(2, 3)<<endl;
    cout<<"4 / 3 = "<<divide(4, 3)<<endl;
    return 0;
}


