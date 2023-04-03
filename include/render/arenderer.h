#pragma once
#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glmpch.h>
#include <map>
#include <string>


class ACamera;

///////////////////////////////////////////////////////////////////////

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

    void SetCamera(ACamera* _camera) { camera = _camera; }

    void SetShaderUniform(const std::string &name, const glm::vec3 &value);
    void SetShaderUniform(const std::string &name, float value);

     GLuint GetShaderProgram(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

    ///////////////////////////////////////////////////////////////////////
    //  VARIABLES
    ///////////////////////////////////////////////////////////////////////

    GLFWwindow *window = nullptr;
    GLuint shaderProgram;

    ///////////////////////////////////////////////////////////////////////

private:

    ///////////////////////////////////////////////////////////////////////
    //  FUNCTIONS
    ///////////////////////////////////////////////////////////////////////

    GLuint CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader);

    GLuint LoadShader(GLenum shaderType, std::string &shaderSource);
    std::string ReadFile(const char *filePath);

    ///////////////////////////////////////////////////////////////////////
    //  VARIABLES
    ///////////////////////////////////////////////////////////////////////

    GLuint VAO, VBO;
    
    std::string vertexShaderSource;
    std::string fragmentShaderSource;
    
    ACamera* camera = nullptr;
    
    std::map<std::pair<std::string, std::string>, GLuint> shaderCache;

    ///////////////////////////////////////////////////////////////////////
};