#include <amaster.h>

using namespace std;

int main()
{
    // Create a renderer
    AMaster& master = AMaster::GetInstance();
    master.MainLoop();

    return 0;
}