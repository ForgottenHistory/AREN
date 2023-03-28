#include <render/arenderer.h>

using namespace std;

int main()
{
    // Create a renderer
    ARenderer renderer;

    while (!glfwWindowShouldClose(renderer.window))
    {
        renderer.Render();
    }

    return 0;
}