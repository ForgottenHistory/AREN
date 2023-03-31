#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

class TestRenderer
{
public:

    int Main();

    GLuint CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader);
    GLuint LoadShader(GLenum shaderType, std::string &shaderSource);
    std::string ReadFile(const char *filePath);

private:

    std::string vertexShaderSource;
    std::string fragmentShaderSource;
};