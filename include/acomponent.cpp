#include "acomponent.h"

#include "render/ashadermanager.h"
#include "amaster.h"
#include "aobject.h"
#include "aobjectmanager.h"
#include "math/amatrix4x4.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRANSFORM COMPONENT
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ATransform::ATransform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale)
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
}

glm::mat4 ATransform::GetModelMatrix() const
{
    glm::mat4 model = glm::mat4(1.0f);

    // Apply translation
    model = glm::translate(model, position);

    // Apply rotation
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    // Apply scale
    model = glm::scale(model, scale);

    return model;
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

glm::vec3 ATransform::GetForward() const
{
    glm::vec3 forward;
    forward.x = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    forward.y = -sin(glm::radians(rotation.x));
    forward.z = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    return glm::normalize(forward);
}

glm::vec3 ATransform::GetRight() const
{
    return glm::normalize(glm::cross(GetForward(), glm::vec3(0.0f, 1.0f, 0.0f)));
}

glm::vec3 ATransform::GetUp() const
{
    return glm::normalize(glm::cross(GetRight(), GetForward()));
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

const AMatrix4x4 &ACamera::GetViewMatrix() const
{
    return viewMatrix;
}

const AMatrix4x4 &ACamera::GetProjectionMatrix() const
{
    return projectionMatrix;
}

void ACamera::UpdateViewMatrix()
{
    // Retrieve position, rotation from the ATransform component
    const glm::vec3 &position = owner->GetComponent<ATransform>()->GetPosition();
    const glm::vec3 &rotation = owner->GetComponent<ATransform>()->GetRotation();

    // Create a rotation matrix based on the Euler angles
    glm::mat4 rotMatrix = glm::mat4(1.0f);
    rotMatrix = glm::rotate(rotMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotMatrix = glm::rotate(rotMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotMatrix = glm::rotate(rotMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    // Default forward vector
    glm::vec4 forward(0.0f, 0.0f, -1.0f, 1.0f);

    // Calculate the direction vector using the rotation matrix
    glm::vec3 direction = glm::normalize(glm::vec3(rotMatrix * forward));

    // Calculate the up vector
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    // Update the view matrix
    viewMatrix = AMatrix4x4(glm::lookAt(position, position + direction, up));
}

void ACamera::UpdateProjectionMatrix()
{
    // Define some projection parameters
    float aspectRatio = 1280.0f / 720.0f;
    float fov = glm::radians(45.0f);
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    // Update the projection matrix
    projectionMatrix = AMatrix4x4(glm::perspective(fov, aspectRatio, nearPlane, farPlane));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AMeshComponent::AMeshComponent()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    material = new AMaterial();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AMeshComponent::~AMeshComponent()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AMeshComponent::SetVertices(const std::vector<AVec3> &_vertices)
{
    vertices = _vertices;

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(AVec3), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(AVec3), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AMeshComponent::SetVertices(const std::vector<AVec3> &_vertices, const std::vector<AVec3> &_normals)
{
    assert(_vertices.size() == _normals.size());

    std::vector<VertexSimple> vertexData(_vertices.size());
    for (size_t i = 0; i < _vertices.size(); ++i)
    {
        vertexData[i].position = _vertices[i];
        vertexData[i].normal = _normals[i];
    }

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(VertexSimple), vertexData.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexSimple), (void *)offsetof(VertexSimple, position));
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexSimple), (void *)offsetof(VertexSimple, normal));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AMeshComponent::SetVertices(const std::vector<AVec3> &_vertices, const std::vector<AVec3> &_normals, const std::vector<glm::vec2> &_texCoords)
{
    assert(_vertices.size() == _normals.size() && _vertices.size() == _texCoords.size());

    std::vector<Vertex> vertexData(_vertices.size());
    for (size_t i = 0; i < _vertices.size(); ++i)
    {
        vertexData[i].position = _vertices[i];
        vertexData[i].normal = _normals[i];
        vertexData[i].texCoords = _texCoords[i];
    }

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(Vertex), vertexData.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    // Texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AMeshComponent::SetIndices(const std::vector<unsigned int> &_indices)
{
    indices = _indices;

    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AMeshComponent::Render()
{
    AShaderManager* shaderManager = AMaster::GetInstance().shaderManager;
    
    GLuint shaderProgram = material->GetShaderProgram();
    glUseProgram(shaderProgram);

    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
    glm::mat4 modelMatrix = owner->GetComponent<ATransform>()->GetModelMatrix();
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    shaderManager->SetShaderUniform(shaderProgram, "u_DiffuseColor", material->GetDiffuseColor());
    shaderManager->SetShaderUniform(shaderProgram, "u_SpecularColor", material->GetSpecularColor());
    shaderManager->SetShaderUniform(shaderProgram, "u_Shininess", material->GetShininess());
    shaderManager->SetShaderUniform(shaderProgram, "u_Texture", 0);

    glBindVertexArray(VAO);

    // Bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, material->GetDiffuseTextureID());

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ASkyboxComponent::ASkyboxComponent()
{
    const GLfloat skyboxVertices[] = {
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f };


    material = new AMaterial();
    material->SetVertexShader("vertex_skybox_shader");
    material->SetDiffuseTexture("default_skybox.png");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ASkyboxComponent::~ASkyboxComponent()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &VBO);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ASkyboxComponent::SetCubemapFaces(const std::vector<std::string> &faces)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ASkyboxComponent::Render()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
