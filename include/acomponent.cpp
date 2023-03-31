#include "acomponent.h"
#include <aobject.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRANSFORM COMPONENT
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ATransform::ATransform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale)
{
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

ACamera::ACamera()
{
    // Initialize the view and projection matrices
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

    std::cout << "Owner pointer: " << owner << std::endl;
    if (owner)
    {
        std::cout << "Owner name: " << owner->name << std::endl;
    }
    else
    {
        std::cout << "Owner is nullptr" << std::endl;
    }

    const glm::vec3 &position = owner->GetComponent<ATransform>()->GetPosition();
    const glm::vec3 &rotation = owner->GetComponent<ATransform>()->GetRotation();

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

AMeshComponent::AMeshComponent()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}

AMeshComponent::~AMeshComponent()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void AMeshComponent::SetVertices(const std::vector<glm::vec3> &_vertices)
{
    vertices = _vertices;
}

const std::vector<glm::vec3> &AMeshComponent::GetVertices() const
{
    return vertices;

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void AMeshComponent::SetIndices(const std::vector<unsigned int> &_indices)
{
    indices = indices;

    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    glBindVertexArray(0);
}

const std::vector<unsigned int> &AMeshComponent::GetIndices() const
{
    return indices;
}

void AMeshComponent::Render()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void AMeshComponent::Update()
{
    // Implement MeshComponent-specific Update logic
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
