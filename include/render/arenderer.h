#pragma once
#include <iostream>
#include <glfw/glfw3.h>

class ARenderer{
public:
    ARenderer();
    ~ARenderer();

    void Init();

void Render();

GLuint LoadShader(GLenum shaderType, std::string &shaderSource);
std::string ReadFile(const char * filePath);

GLFWwindow *window = nullptr;

private: 
    // Triangle data
    GLfloat vertices[9] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    GLuint indices[3] = {
        0, 1, 2
    };

    // OpenGL objects
    GLuint VAO, VBO, EBO;

    std::string vertexShaderSource;
    std::string fragmentShaderSource;
};