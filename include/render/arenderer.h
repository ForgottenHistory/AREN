#pragma once
#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glmpch.h>
#include <map>
#include <string>
#include "math/AVec3.h"
#include "ashader.h"

class ACamera;

///////////////////////////////////////////////////////////////////////

class ARenderer
{
public:

    ///////////////////////////////////////////////////////////////////////
    //  FUNCTIONS
    ///////////////////////////////////////////////////////////////////////

    // Static method to get the singleton instance
    static ARenderer& GetInstance()
    {
        static ARenderer instance; // Only created once
        return instance;
    }

    ~ARenderer();

    void Init();

    void Render();

    void SetCamera(ACamera* _camera) { camera = _camera; }
    ACamera* GetCamera() { return camera; }

    void SetShaderUniform(GLuint shaderProgram, const std::string &name, const AVec3 &value);
    void SetShaderUniform(GLuint shaderProgram, const std::string &name, float value);

    GLuint GetShaderProgram(const std::string &vertexShaderName, const std::string &fragmentShaderName);

    ///////////////////////////////////////////////////////////////////////
    //  VARIABLES
    ///////////////////////////////////////////////////////////////////////

    GLFWwindow *window = nullptr;
    GLuint shaderProgram;

    ///////////////////////////////////////////////////////////////////////

private:
    
    ARenderer();

    ///////////////////////////////////////////////////////////////////////
    //  FUNCTIONS
    ///////////////////////////////////////////////////////////////////////
    
    void CreateShaders();

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

    AShader defaultShader;

    ///////////////////////////////////////////////////////////////////////
    
    // Private copy constructor and assignment operator to prevent copying
    ARenderer(const ARenderer&) = delete;
    ARenderer& operator=(const ARenderer&) = delete;
};
