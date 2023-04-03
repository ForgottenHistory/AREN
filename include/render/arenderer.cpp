#include "arenderer.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <glmpch.h>
#include <time.h>
#include <acomponent.h>
#include "aobject.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTOR / DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ARenderer::ARenderer()
{
    std::cout << "ARenderer created" << std::endl;
    Init();
}
ARenderer::~ARenderer()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  INITIALIZATION
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ARenderer::Init()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    // Create a window
    window = glfwCreateWindow(1280, 720, "AREN", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    // Set the window's OpenGL context
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return;
    }

    // glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);

    // Load shaders
    vertexShaderSource = ReadFile("shaders/vertex_shader.glsl");
    fragmentShaderSource = ReadFile("shaders/fragment_shader.glsl");
    GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    // Create and link the shader program
    shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);

    // Clean up shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  RENDERING
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ARenderer::Render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);

    if (camera)
    {
        GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
        GLint projectionLoc = glGetUniformLocation(shaderProgram, "projection");

        glm::vec3 cameraPos = camera->owner->GetComponent<ATransform>()->GetPosition();

        // Set view position uniform
        GLint viewPosLoc = glGetUniformLocation(shaderProgram, "u_ViewPos");
        glUniform3f(viewPosLoc, cameraPos.x, cameraPos.y, cameraPos.z);

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera->GetProjectionMatrix()));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  SHADERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ARenderer::SetShaderUniform(const std::string &name, const glm::vec3 &value)
{
    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    glUniform3f(location, value.x, value.y, value.z);
}

void ARenderer::SetShaderUniform(const std::string &name, float value)
{
    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    glUniform1f(location, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GLuint ARenderer::GetShaderProgram(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
    // Check if the shader program is already cached
    auto key = std::make_pair(vertexShaderPath, fragmentShaderPath);
    auto it = shaderCache.find(key);
    if (it != shaderCache.end()) {
        return it->second;
    }

    // Load shaders
    std::string vertexShaderSource = ReadFile(vertexShaderPath.c_str());
    std::string fragmentShaderSource = ReadFile(fragmentShaderPath.c_str());
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

GLuint ARenderer::CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader)
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

GLuint ARenderer::LoadShader(GLenum shaderType, std::string &shaderSource)
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

std::string ARenderer::ReadFile(const char *filePath)
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
