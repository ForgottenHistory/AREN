#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <render/arenderer.h>
#include <time.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <time.h>

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

    // Load shaders
    vertexShaderSource = ReadFile("shaders/vertex_shader.glsl");
    fragmentShaderSource = ReadFile("shaders/fragment_shader.glsl");
    GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    // Create and link the shader program
    shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);

    // Set up the vertex data and configure the VAO, VBO, and EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind the VAO
    glBindVertexArray(VAO);

    // Bind and set the vertex buffer data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind and set the element buffer data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Configure the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);

    // Unbind the VAO
    glBindVertexArray(0);

    // Clean up shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Create a model matrix
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

    // Create a view matrix
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    view = glm::lookAt(cameraPos, cameraTarget, cameraUp);

    // Create a projection matrix
    float aspectRatio = 1280.0f / 720.0f;
    float fov = glm::radians(45.0f);
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    projection = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  RENDERING
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Ran in main loop (main.cpp)
void ARenderer::Render()
{
    // Update the elapsedTime variable
    float sinTime = Time::sinTime;
    float cosTime = Time::cosTime;

    // Calculate the offset based on elapsed time
    float offsetX = sinTime * 0.5f;
    float offsetY = cosTime * 0.5f;

    // Clear the color buffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Rendering tasks
    glUseProgram(shaderProgram);
    glUniform2f(glGetUniformLocation(shaderProgram, "uOffset"), offsetX, offsetY);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
    GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLint projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Unbind the VAO and shader program
    glBindVertexArray(0);
    glUseProgram(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  SHADERS
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
        std::cerr << "Failed to link shader program:\n" << log.data() << std::endl;

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
        std::cerr << "Failed to compile shader:\n" << log.data() << std::endl;

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

    if (!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
