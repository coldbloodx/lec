#include <iostream>
#include <utility>
#include <string>

using namespace std;

class FirstClass 
{
public:
   FirstClass () = default;

   FirstClass (const FirstClass& fc) 
   {
       cout<<"FC copy constructor"<<endl;
   }

   FirstClass (const FirstClass&& fc)
   {
       cout<<"FC move constructor"<<endl;
   }

    virtual ~FirstClass () = default;

private:
    /* data */
};

class SecondClass 
{
public:
    SecondClass () = default;
    virtual ~SecondClass () = default;

    SecondClass (const SecondClass& sc):
        fc_member(sc.fc_member)
    {
        cout<<"SC copy constructor"<<endl;
    }

    SecondClass (const SecondClass&& sc):
        fc_member(std::move(sc.fc_member))
    {
        cout<<"SC move constructor"<<endl;
    }

private:
    /* data */
    FirstClass fc_member;
};


int main()
{
    SecondClass sc;

    cout<<"following is invoking copy constructor"<<endl;
    SecondClass sc1(sc);

    cout<<"following is invoking move constructor"<<endl;
    SecondClass sc2(std::move(sc));

    return 0;
}
