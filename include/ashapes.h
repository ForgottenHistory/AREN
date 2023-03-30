#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

class APrimitiveShape {
public:
    // Virtual destructor to ensure proper cleanup of derived classes.
    virtual ~APrimitiveShape() {}

    // Initialize and set up shape data for rendering.
    virtual void Setup() = 0;

    // Render the shape.
    virtual void Render() = 0;

protected:
    // Function to generate and bind VAO, VBO, and EBO.
    virtual void SetupBuffers() = 0;

    // Generate vertex data for the shape.
    virtual std::vector<GLfloat> GenerateVertexData() const = 0;

    // Generate index data for the shape.
    virtual std::vector<GLuint> GenerateIndexData() const = 0;

    // Vertex Array Object (VAO) for the shape.
    GLuint VAO;

    // Vertex Buffer Object (VBO) for the shape.
    GLuint VBO;

    // Element Buffer Object (EBO) for the shape.
    GLuint EBO;
};
