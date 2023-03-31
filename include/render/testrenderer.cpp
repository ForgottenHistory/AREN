#include "render/testrenderer.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

int TestRenderer::Main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(1280, 720, "Simple Triangle", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    vertexShaderSource = ReadFile("shaders/vertex_shader.glsl");
    fragmentShaderSource = ReadFile("shaders/fragment_shader.glsl");
    GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    GLuint shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  SHADERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GLuint TestRenderer::CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader)
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

GLuint TestRenderer::LoadShader(GLenum shaderType, std::string &shaderSource)
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

std::string TestRenderer::ReadFile(const char *filePath)
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
