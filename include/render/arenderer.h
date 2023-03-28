#pragma once
#include <iostream>
#include <glew/include/GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>

class ARenderer{
public:
    ARenderer();
    ~ARenderer();

    void Init();
    void Render();

    GLuint LoadShader(GLenum shaderType, const std::string& shaderSource);

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
};