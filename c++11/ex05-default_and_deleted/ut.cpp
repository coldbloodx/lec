#include <iostream>
using namespace std;

class DefaultAndDelete 
{
public:
    //default keyword will tell compiler to generate
    //default implemention for the function
    DefaultAndDelete () = default;
    virtual ~DefaultAndDelete () = default;
    DefaultAndDelete& operator =(const DefaultAndDelete& src) = delete;
    DefaultAndDelete(const DefaultAndDelete& src) = delete;
    void output();
private:
    static const int int_member = 0;
};

void DefaultAndDelete::output()
{
    cout<<"int_member:"<<int_member<<endl;
}

int main()
{
    DefaultAndDelete dnd;
    //following lines could produce compilation errors
    //because the copy constructor and assign operator
    //are decorated by delete
    //DefaultAndDelete dnd1(dnd);
    //DefaultAndDelete dnd2 = dnd;
    dnd.output();
    return 0;
}
