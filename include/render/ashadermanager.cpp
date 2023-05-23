#include "render/ashadermanager.h"

#include <fstream>
#include <vector>
#include "ashadermanager.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AShaderManager::AShaderManager()
{
}

AShaderManager::~AShaderManager()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AShaderManager::Initialize()
{
    CreateShaders();
}

void AShaderManager::Render(AVec3 cameraPos, AMatrix4x4 viewMatrix, AMatrix4x4 projectionMatrix)
{
    for (auto &shaderPair : shaderCache)
        {
            GLuint shaderProgram = shaderPair.second;
            glUseProgram(shaderProgram);

            GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
            GLint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
            GLint viewPosLoc = glGetUniformLocation(shaderProgram, "u_ViewPos");

            glUniform3f(viewPosLoc, cameraPos.x, cameraPos.y, cameraPos.z);
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix.ToGLM()));
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix.ToGLM()));
        }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  SHADERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AShaderManager::SetShaderUniform(GLuint shaderProgram, const std::string &name, const AVec3 &value)
{
    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    glUniform3f(location, value.x, value.y, value.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AShaderManager::SetShaderUniform(GLuint shaderProgram, const std::string &name, float value)
{
    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    glUniform1f(location, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GLuint AShaderManager::GetShaderProgram(const std::string &vertexShaderName, const std::string &fragmentShaderName)
{
    // Check if the shader program is already cached
    auto key = std::make_pair(vertexShaderName, fragmentShaderName);
    auto it = shaderCache.find(key);
    if (it != shaderCache.end())
    {
        return it->second;
    }

    // Load shaders
    std::string vertexShaderSource = ReadFile(("shaders/" + vertexShaderName + ".glsl").c_str());
    std::string fragmentShaderSource = ReadFile(("shaders/" + fragmentShaderName + ".glsl").c_str());
    GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    // Create and link the shader program
    GLuint shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);

    // Don't forget to clean up the shader objects after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Cache the shader program
    shaderCache[key] = shaderProgram;

    return shaderProgram;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AShaderManager::CreateShaders()
{
    // Load shaders
    vertexShaderSource = ReadFile("shaders/vertex_shader.glsl");
    fragmentShaderSource = ReadFile("shaders/fragment_shader.glsl");
    GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    // Clean up shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GLuint AShaderManager::CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader)
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

GLuint AShaderManager::LoadShader(GLenum shaderType, std::string &shaderSource)
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

std::string AShaderManager::ReadFile(const char *filePath)
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
