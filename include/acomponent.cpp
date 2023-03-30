#include "acomponent.h"
#include <aobject.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRANSFORM COMPONENT
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ATransform::ATransform(AObject *_owner, const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale)
{
    owner = _owner;
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;    
}

const glm::vec3 &ATransform::GetPosition() const
{
    return position;
}

const glm::vec3 &ATransform::GetRotation() const
{
    return rotation;
}

const glm::vec3 &ATransform::GetScale() const
{
    return scale;
}

void ATransform::SetPosition(const glm::vec3 &_position)
{
    position = _position;
}

void ATransform::SetRotation(const glm::vec3 &_rotation)
{
    rotation = _rotation;
}

void ATransform::SetScale(const glm::vec3 &_scale)
{
    scale = _scale;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CAMERA
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ACamera::ACamera(AObject *_owner)
{
    owner = _owner;

    // Initialize the view and projection matrices
    Update();
}

void ACamera::Update()
{
    UpdateViewMatrix();
    UpdateProjectionMatrix();
}

const glm::mat4 &ACamera::GetViewMatrix() const
{
    return viewMatrix;
}

const glm::mat4 &ACamera::GetProjectionMatrix() const
{
    return projectionMatrix;
}

void ACamera::UpdateViewMatrix()
{
    // Retrieve position, rotation from the ATransform component
    const glm::vec3 &position = glm::vec3(0.0f, 0.0f, 0.0f);
    const glm::vec3 &rotation = glm::vec3(0.0f, 0.0f, 0.0f);

    // Calculate direction vector based on rotation
    glm::vec3 direction;
    direction.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    direction.y = sin(glm::radians(rotation.x));
    direction.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    direction = glm::normalize(direction);

    // Calculate the up vector
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    // Update the view matrix
    viewMatrix = glm::lookAt(position, position + direction, up);
}

void ACamera::UpdateProjectionMatrix()
{
    // Define some projection parameters
    float aspectRatio = 1280.0f / 720.0f;
    float fov = glm::radians(45.0f);
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    // Update the projection matrix
    projectionMatrix = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////