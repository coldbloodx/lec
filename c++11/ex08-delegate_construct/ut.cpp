#include <iostream>
using namespace std;

class DelegateConstruct 
{
public:
    DelegateConstruct (int int_param):int_member(int_param){};
    //DelegateConstruct():DelegateConstruct(10){};
    void output(){cout<<"int_param:"<<int_member<<endl;};
    virtual ~DelegateConstruct () = default;

private:
    /* data */
    int int_member;
};

int main()
{
    //DelegateConstruct dc();
    //dc.output();
    
    DelegateConstruct dc(10);
    dc.output();
    return 0;
}
