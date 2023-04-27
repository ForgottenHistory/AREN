#pragma once 
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <string>

class AShader {
    public:
    std::string vertexShaderSource;
    std::string fragmentShaderSource;
    GLuint shaderProgram;
};