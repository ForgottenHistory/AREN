#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <fstream>
#include <render/arenderer.h>

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

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return;
    }

    // Load shaders
    vertexShaderSource = ReadFile("shaders/vertex_shader.glsl");
    fragmentShaderSource = ReadFile("shaders/fragment_shader.glsl");
}

// Ran in main loop (main.cpp)
void ARenderer::Render()
{
    // Check if the window should close
    if (glfwWindowShouldClose(window))
        return;

    // Clear the color buffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap the front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process window events
    glfwPollEvents();
}

GLuint ARenderer::LoadShader(GLenum shaderType, std::string &shaderSource)
{
    GLuint shader = 2;


    return shader;
}

std::string ARenderer::ReadFile(const char *filePath)
{
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if (!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

