#pragma once
#include <glmpch.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <string>
#include <vector>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COMPONENT BASE CLASS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

struct VertexSimple {
    glm::vec3 position;
    glm::vec3 normal;
};

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class AMaterial
{
public:
    AMaterial();
    ~AMaterial() {}

    void SetDiffuseColor(const glm::vec3 &_diffuseColor) { diffuseColor = _diffuseColor; }
    const glm::vec3 &GetDiffuseColor() const { return diffuseColor; }

    void SetSpecularColor(const glm::vec3 &_specularColor) { specularColor = _specularColor; }
    const glm::vec3 &GetSpecularColor() const { return specularColor; }

    void SetShininess(const float _shininess) { shininess = _shininess; }
    const float GetShininess() const { return shininess; }

    void SetVertexShader(const std::string &_vertexShader);
    const std::string &GetVertexShader() const { return vertexShader; }

    void SetFragmentShader(const std::string &_fragmentShader);
    const std::string &GetFragmentShader() const { return fragmentShader; }

    void SetShaders(const std::string &_vertexShader, const std::string &_fragmentShader);

    void SetDiffuseTexture(const std::string &_diffuseTexture);
    const std::string &GetDiffuseTexture() const { return diffuseTexture; }
    GLuint GetDiffuseTextureID() const { return diffuseTextureID; }

    GLuint GetShaderProgram() const { return shaderProgram; }

private:
    glm::vec3 diffuseColor = glm::vec3(1.0f);
    glm::vec3 specularColor = glm::vec3(0.0f);

    std::string diffuseTexture = "default_texture";
    GLuint diffuseTextureID = 0;

    std::string vertexShader = "vertex_shader";
    std::string fragmentShader = "fragment_shader";
    GLuint shaderProgram = 0;

    float shininess = 1.0f;
};

class AMeshComponent : public Component
{
public:
    AMeshComponent();
    ~AMeshComponent();

    void SetVertices(const std::vector<glm::vec3> &_vertices);
    void SetVertices(const std::vector<glm::vec3>& _vertices, const std::vector<glm::vec3>& _normals);
    void SetVertices(const std::vector<glm::vec3>& _vertices, const std::vector<glm::vec3>& _normals, const std::vector<glm::vec2>& _texCoords);

    const std::vector<glm::vec3> &GetVertices() const;

    void SetIndices(const std::vector<unsigned int> &_indices);
    const std::vector<unsigned int> &GetIndices() const;

    // Override the Update function if needed
    void Update() override;
    void Render();

    AMaterial* material;

private:
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;

    // OpenGL-specific data
    GLuint VAO, VBO, EBO;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
