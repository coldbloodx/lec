//testing make file
//entry for the whole program

#include <iostream>
extern "C"
{
    extern double add(double, double);
    extern double sub(double, double);
    extern double mul(double, double);
    extern double div(double, double);
};
using namespace std;

int main()
{
    cout<<"1 + 1 = "<<add(1, 1)<<endl;
    cout<<"2 - 1 = "<<sub(2, 1)<<endl;
    cout<<"2 x 3 = "<<mul(2, 3)<<endl;
    cout<<"4 / 3 = "<<div(4, 3)<<endl;
    return 0;
}


