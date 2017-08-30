#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> int_vector;
    for (int i = 0; i < 100; i++) 
    {
        int_vector.push_back(i);
    }

    //#keyword auto and decltype.
    typedef decltype (int_vector.begin()) VIT;
    auto iter_begin = int_vector.begin();
    VIT iter_end = int_vector.end();

    copy(iter_begin, iter_end, ostream_iterator<int>(cout, " "));
    cout<<endl;
    return 0;
}
