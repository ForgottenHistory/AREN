#include <iostream>
#include <vector>
#include <string>
#include <test.h>

using namespace std;

int main()
{
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;

    cout << fname(1, 2, 3) << endl;
    int x;
    cin >> x;
    return 0;
}