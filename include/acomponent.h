#pragma once
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COMPONENT BASE CLASS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AObject;
class Component {
public:
    virtual ~Component() {}

    virtual void Update() = 0;
    
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRANSFORM COMPONENT
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ATransform : public Component {
    public:
    ATransform(const glm::vec3& position = glm::vec3(0.0f),
               const glm::vec3& rotation = glm::vec3(0.0f),
               const glm::vec3& scale = glm::vec3(1.0f));
    
    // Getters
    const glm::vec3& GetPosition() const;
    const glm::vec3& GetRotation() const;
    const glm::vec3& GetScale() const;

    // Setters
    void SetPosition(const glm::vec3& position);
    void SetRotation(const glm::vec3& rotation);
    void SetScale(const glm::vec3& scale);

    void Update() override {
        // Example code
    }

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

class ExampleComponent : public Component {
public:
    ExampleComponent() { std::cout << "ExampleComponent created" << std::endl; }

    void Update() override {
        // Example code
    }
};