#include <iostream>
#include <vector>
#include <string>
#include <debug/test.h>
#include <glew/include/GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>

using namespace std;

int main()
{
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;

    GLuint vao = 2;
    cout << vao << endl;

    cout << fname(1, 2, 3) << endl;
    int x;
    cin >> x;
    return 0;
}