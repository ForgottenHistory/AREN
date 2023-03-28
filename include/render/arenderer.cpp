#include <render/arenderer.h>
#include <glew/include/GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>
#include <iostream>

ARenderer::ARenderer()
{
    std::cout << "ARenderer created" << std::endl;
    Init();
}
ARenderer::~ARenderer()
{
}

void ARenderer::Init()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    // Create a window
    window = glfwCreateWindow(1280, 720, "AREN", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    // Set the window's OpenGL context
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    GLenum glewInitResult = glewInit();
    if (glewInitResult != GLEW_OK)
    {
        glfwTerminate();
        return;
    }

    // Set the OpenGL viewport
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
}

// Ran in main loop (main.cpp)
void ARenderer::Render()
{
    // Clear the screen
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap buffers and poll events
    glfwSwapBuffers(window);
    glfwPollEvents();
}