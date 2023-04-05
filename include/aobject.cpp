#include "aobject.h"
#include "acomponent.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<glm::vec3> AObject::CalculateNormals(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices)
{
    std::vector<glm::vec3> normals(vertices.size(), glm::vec3(0.0f));

    for (size_t i = 0; i < indices.size(); i += 3)
    {
        glm::vec3 v1 = vertices[indices[i + 1]] - vertices[indices[i]];
        glm::vec3 v2 = vertices[indices[i + 2]] - vertices[indices[i]];
        glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

        normals[indices[i]] += normal;
        normals[indices[i + 1]] += normal;
        normals[indices[i + 2]] += normal;
    }

    for (glm::vec3& normal : normals)
    {
        normal = glm::normalize(normal);
    }

    return normals;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CUBE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ACube::ACube()
{
    // Create a mesh component and set the cube-specific vertex and index data
    AMeshComponent *meshComponent = new AMeshComponent();

    std::vector<glm::vec3> vertices = {
        {-0.5f, -0.5f, -0.5f},
        {0.5f, -0.5f, -0.5f},
        {0.5f, 0.5f, -0.5f},
        {-0.5f, 0.5f, -0.5f},
        {-0.5f, -0.5f, 0.5f},
        {0.5f, -0.5f, 0.5f},
        {0.5f, 0.5f, 0.5f},
        {-0.5f, 0.5f, 0.5f}};

    std::vector<glm::vec2> texCoords = {
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f},
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f}};

    std::vector<unsigned int> indices = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        0, 1, 5, 5, 4, 0,
        2, 3, 7, 7, 6, 2,
        0, 3, 7, 7, 4, 0,
        1, 2, 6, 6, 5, 1};

    std::vector<glm::vec3> normals = CalculateNormals(vertices, indices);

    meshComponent->SetVertices(vertices, normals, texCoords);
    meshComponent->SetIndices(indices);

    // Add the mesh component to the cube object
    AddComponent(meshComponent);

    // Initialize the transform component
    transform = new ATransform();
    AddComponent(transform);
}

ACube::~ACube()
{
}

void ACube::PreStart()
{
    // Implement any cube-specific pre-start logic here
}

void ACube::Start()
{
    // Implement any cube-specific start logic here
}

void ACube::Update()
{
    // Implement any cube-specific update logic here

    // Update components
    UpdateComponents();
}

void ACube::SecondUpdate()
{
    // Implement any cube-specific second update logic here
}

void ACube::Render()
{
    AMeshComponent *meshComponent = GetComponent<AMeshComponent>();
    if (meshComponent != nullptr)
    {
        meshComponent->Render();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
