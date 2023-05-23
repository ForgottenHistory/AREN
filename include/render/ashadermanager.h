#pragma once
#include "glmpch.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <string>
#include <iostream>
#include <map>

#include "math/avec3.h"
#include "math/amatrix4x4.h"
#include "render/ashader.h"

class AShaderManager
{
    public:

        ///////////////////////////////////////////////////////////////////////
        //  FUNCTIONS
        ///////////////////////////////////////////////////////////////////////

        AShaderManager();
        ~AShaderManager();

        void Initialize();

        void Render(AVec3 cameraPos, AMatrix4x4 viewMatrix, AMatrix4x4 projectionMatrix);

        void SetShaderUniform(GLuint shaderProgram, const std::string &name, const AVec3 &value);
        void SetShaderUniform(GLuint shaderProgram, const std::string &name, float value);

        GLuint GetShaderProgram(const std::string &vertexShaderName, const std::string &fragmentShaderName);

        ///////////////////////////////////////////////////////////////////////
        //  VARIABLES
        ///////////////////////////////////////////////////////////////////////

        std::map<std::string, GLuint> shaderPrograms;

        ///////////////////////////////////////////////////////////////////////

    private:

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

        std::string vertexShaderSource;
        std::string fragmentShaderSource;

        std::map<std::pair<std::string, std::string>, GLuint> shaderCache;

        AShader defaultShader;

        ///////////////////////////////////////////////////////////////////////
};