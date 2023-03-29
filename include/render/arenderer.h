#pragma once
#include <iostream>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ARenderer
{
public:

    ///////////////////////////////////////////////////////////////////////
    //  FUNCTIONS
    ///////////////////////////////////////////////////////////////////////

    ARenderer();
    ~ARenderer();

    void Init();

    void Render();

    ///////////////////////////////////////////////////////////////////////
    //  VARIABLES
    ///////////////////////////////////////////////////////////////////////

    GLuint LoadShader(GLenum shaderType, std::string &shaderSource);
    std::string ReadFile(const char *filePath);

    GLFWwindow *window = nullptr;

    ///////////////////////////////////////////////////////////////////////

private:

    ///////////////////////////////////////////////////////////////////////
    //  FUNCTIONS
    ///////////////////////////////////////////////////////////////////////

    GLuint CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader);

    ///////////////////////////////////////////////////////////////////////
    //  VARIABLES
    ///////////////////////////////////////////////////////////////////////

    // Square data (two triangles)
    GLfloat vertices[12] = {
        -0.5f, -0.5f, 0.0f, // Bottom-left vertex
        0.5f, -0.5f, 0.0f, // Bottom-right vertex
        0.5f,  0.5f, 0.0f, // Top-right vertex
        -0.5f,  0.5f, 0.0f  // Top-left vertex
    };

    GLuint indices[6] = {
        0, 1, 2, // First triangle
        0, 2, 3  // Second triangle
};

    // OpenGL objects
    GLuint VAO, VBO, EBO;
    GLuint shaderProgram;

    std::string vertexShaderSource;
    std::string fragmentShaderSource;

    glm::mat4 view, projection, model;
    
    ///////////////////////////////////////////////////////////////////////
};