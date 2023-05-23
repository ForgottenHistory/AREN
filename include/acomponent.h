#pragma once
#include <glmpch.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <string>
#include <vector>
#include <iostream>
#include "render/amaterial.h"
#include "math/amatrix4x4.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COMPONENT BASE CLASS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AVec3;
class AObject;

class Component
{
public:
    virtual ~Component() {}

    virtual void Update() {}
    virtual void Render() {}

    void SetOwner(AObject *_owner)
    {
        owner = _owner;
    }

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

    glm::vec3 GetForward() const;

    glm::vec3 GetRight() const;

    glm::vec3 GetUp() const;

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
    const AMatrix4x4 &GetViewMatrix() const;
    const AMatrix4x4 &GetProjectionMatrix() const;

    void Update() override;

    void UpdateViewMatrix();
    void UpdateProjectionMatrix();

private:
    // Matrices
    AMatrix4x4 viewMatrix;
    AMatrix4x4 projectionMatrix;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct VertexSimple {
    AVec3 position;
    AVec3 normal;
};

struct Vertex {
    AVec3 position;
    AVec3 normal;
    glm::vec2 texCoords;
};

class AMeshComponent : public Component
{
public:
    AMeshComponent();
    ~AMeshComponent();

    void SetVertices(const std::vector<AVec3> &_vertices);
    void SetVertices(const std::vector<AVec3>& _vertices, const std::vector<AVec3>& _normals);
    void SetVertices(const std::vector<AVec3>& _vertices, const std::vector<AVec3>& _normals, const std::vector<glm::vec2>& _texCoords);

    void SetIndices(const std::vector<unsigned int> &_indices);

    void Render() override;

    AMaterial* material;

private:
    std::vector<AVec3> vertices;
    std::vector<unsigned int> indices;

    // OpenGL-specific data
    GLuint VAO, VBO, EBO;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ASkyboxComponent : public Component
{
public:
    ASkyboxComponent();
    ~ASkyboxComponent();

    void SetCubemapFaces(const std::vector<std::string>& faces);

    void Render() override;

    AMaterial* material;

private:

    // OpenGL-specific data
    GLuint VAO, VBO;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
