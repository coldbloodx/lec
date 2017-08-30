#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
    execlp("/bin/ls", "/bin/ls", "/", NULL);
    cout<<"1234567890"<<endl;
    return 0;
}
