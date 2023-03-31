#pragma once
#include <iostream>
#include <vector>
#include <glad/glad.h> 
#include <glfw/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COMPONENT BASE CLASS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AObject;
class Component
{
public:
    virtual ~Component() {}

    virtual void Update() {}

    void SetOwner(AObject *_owner)
    {
        owner = _owner;
    }

protected:
    AObject *owner;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRANSFORM COMPONENT
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ATransform : public Component
{
public:
    ATransform(const glm::vec3 &position = glm::vec3(0.0f),
               const glm::vec3 &rotation = glm::vec3(0.0f),
               const glm::vec3 &scale = glm::vec3(1.0f));

    // Getters
    glm::mat4 GetModelMatrix() const;
    const glm::vec3 &GetPosition() const;
    const glm::vec3 &GetRotation() const;
    const glm::vec3 &GetScale() const;

    // Setters
    void SetPosition(const glm::vec3 &position);
    void SetRotation(const glm::vec3 &rotation);
    void SetScale(const glm::vec3 &scale);

private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CAMERA
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ACamera : public Component
{
public:
    // Constructor
    ACamera();

    // Accessor functions
    const glm::mat4 &GetViewMatrix() const;
    const glm::mat4 &GetProjectionMatrix() const;

    void Update() override;

    void UpdateViewMatrix();
    void UpdateProjectionMatrix();

private:
    // Matrices
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AMeshComponent : public Component {
public:
    AMeshComponent();
    ~AMeshComponent();

    void SetVertices(const std::vector<glm::vec3>& _vertices);
    const std::vector<glm::vec3>& GetVertices() const;

    void SetIndices(const std::vector<unsigned int>& _indices);
    const std::vector<unsigned int>& GetIndices() const;

    // Override the Update function if needed
    void Update() override;
    void Render();

private:
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;

    // OpenGL-specific data
    GLuint VAO, VBO, EBO;
};