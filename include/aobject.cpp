#include "aobject.h"
#include "acomponent.h"

ACube::ACube()
{
    // Create a mesh component and set the cube-specific vertex and index data
    AMeshComponent *meshComponent = new AMeshComponent();

    std::vector<glm::vec3> cubeVertices = {
        {-0.5f, -0.5f, -0.5f},
        {0.5f, -0.5f, -0.5f},
        {0.5f, 0.5f, -0.5f},
        {-0.5f, 0.5f, -0.5f},
        {-0.5f, -0.5f, 0.5f},
        {0.5f, -0.5f, 0.5f},
        {0.5f, 0.5f, 0.5f},
        {-0.5f, 0.5f, 0.5f}};

    std::vector<unsigned int> cubeIndices = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        0, 1, 5, 5, 4, 0,
        2, 3, 7, 7, 6, 2,
        0, 3, 7, 7, 4, 0,
        1, 2, 6, 6, 5, 1};

    meshComponent->SetVertices(cubeVertices);
    meshComponent->SetIndices(cubeIndices);

    // Add the mesh component to the cube object
    AddComponent<AMeshComponent>(meshComponent);

    // Initialize the transform component
    transform = new ATransform();
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
    // Implement any cube-specific rendering logic here

    // For example, you can call the mesh component's rendering function
    AMeshComponent *meshComponent = GetComponent<AMeshComponent>();
    if (meshComponent != nullptr)
    {
        meshComponent->Render();
    }
}