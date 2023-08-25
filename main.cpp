#include <iostream>
#include <vector>

using namespace std;

int main()
{

    std::vector<char> v;
    v.push_back('a');

    std::string s;

    for (auto i = v.rbegin(); i != v.rend(); ++i)
    {
        s += (char)(*i + '0');
        cout << *i << endl;
    }

    cout << "Hello World!" << endl;
    return 0;
}