#include <render/arenderer.h>

using namespace std;

int main()
{
    // Create a renderer
    ARenderer renderer;

    while (!glfwWindowShouldClose(renderer.window))
    {
        renderer.Render();
 
        // Swap the front and back buffers
        glfwSwapBuffers(renderer.window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}