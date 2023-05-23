#include "arenderer.h"

#include <iostream>
#include <vector>

#include "math/amath.h"
#include "math/amatrix4x4.h"
#include "render/ashadermanager.h"
#include "amaster.h"
#include "acomponent.h"
#include "aobject.h"
#include "time.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTOR / DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ARenderer::ARenderer()
{
    std::cout << "ARenderer created" << std::endl;
}
ARenderer::~ARenderer()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  INITIALIZATION
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ARenderer::Initialize()
{
    AMaster& master = AMaster::GetInstance();
    shaderManager = master.shaderManager;

    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    // Create a window
    window = glfwCreateWindow(1280, 720, "AREN", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    // Set the window's OpenGL context
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return;
    }

    // glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  RENDERING
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ARenderer::Render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (camera)
    {
        AMatrix4x4 viewMatrix = camera->GetViewMatrix();
        AMatrix4x4 projectionMatrix = camera->GetProjectionMatrix();
        glm::vec3 cameraPos = camera->owner->GetComponent<ATransform>()->GetPosition();
        
        shaderManager->Render(cameraPos, viewMatrix, projectionMatrix);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
