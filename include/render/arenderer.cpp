#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <render/arenderer.h>
#include <time.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <time.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTOR / DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ARenderer::ARenderer()
{
    std::cout << "ARenderer created" << std::endl;
    Init();
}
ARenderer::~ARenderer()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  INITIALIZATION
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    // Create and link the shader program
    shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);

    // Clean up shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  RENDERING
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Ran in main loop (main.cpp)
void ARenderer::Render()
{
    // Clear the color buffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  SHADERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GLuint ARenderer::CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
    // Create the shader program object
    GLuint shaderProgram = glCreateProgram();
    if (shaderProgram == 0)
    {
        std::cerr << "Failed to create shader program" << std::endl;
        return 0;
    }

    // Attach the vertex and fragment shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Link the shader program
    glLinkProgram(shaderProgram);

    // Check the linking status
    GLint linkStatus;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);
    if (!linkStatus)
    {
        // If the linking failed, retrieve and print the linking log
        GLint logLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> log(logLength);
        glGetProgramInfoLog(shaderProgram, logLength, nullptr, log.data());
        std::cerr << "Failed to link shader program:\n"
                  << log.data() << std::endl;

        // Clean up the shader program object
        glDeleteProgram(shaderProgram);
        return 0;
    }

    // If the linking succeeded, return the shader program object
    return shaderProgram;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GLuint ARenderer::LoadShader(GLenum shaderType, std::string &shaderSource)
{
    // Create a shader object
    GLuint shader = glCreateShader(shaderType);
    if (shader == 0)
    {
        std::cerr << "Failed to create shader" << std::endl;
        return 0;
    }

    // Attach the shader source code to the shader object
    const char *sourceCString = shaderSource.c_str();
    glShaderSource(shader, 1, &sourceCString, nullptr);

    // Compile the shader
    glCompileShader(shader);

    // Check the compilation status
    GLint compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    if (!compileStatus)
    {
        // If the compilation failed, retrieve and print the compilation log
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> log(logLength);
        glGetShaderInfoLog(shader, logLength, nullptr, log.data());
        std::cerr << "Failed to compile shader:\n"
                  << log.data() << std::endl;

        // Clean up the shader object
        glDeleteShader(shader);
        return 0;
    }

    // If the compilation succeeded, return the shader object
    return shader;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string ARenderer::ReadFile(const char *filePath)
{
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if (!fileStream.is_open())
    {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while (!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
