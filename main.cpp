#include <render/arenderer.h>
#include <time.h>
#include <cmath>

using namespace std;

int main()
{
    // Create a renderer
    ARenderer renderer;

    float printTime = 1.0f;
    while (!glfwWindowShouldClose(renderer.window))
    {
        Time::UpdateTime();

        renderer.Render();

        float elapsedTime = Time::elapsedTime;

        if (elapsedTime >= printTime)
        {
            Time::PrintTime();
            printTime = elapsedTime + 1.0f;
        }

        // Swap the front and back buffers
        glfwSwapBuffers(renderer.window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}