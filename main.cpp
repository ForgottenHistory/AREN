#include <iostream>
#include <glew/include/GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>
#include <render/arenderer.h>

using namespace std;

int main()
{
    // Create a renderer
    ARenderer renderer;
    renderer.Init();
    
    while (!glfwWindowShouldClose(renderer.window))
    {
        renderer.Render();
    }

    glfwTerminate();
    return 0;
}