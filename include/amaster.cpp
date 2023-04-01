#include <amaster.h>
#include <aobject.h>
#include <amanager.h>
#include <render/arenderer.h>
#include <time.h>
#include "acomponent.h" 
#include "render/testrenderer.h"
#include "components/cameracontroller.h"

#include "debug/test.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AMaster::AMaster()
{
        // Create a test renderer
    //TestRenderer* testRenderer = new TestRenderer();
    //testRenderer->Main();

    renderer = new ARenderer();
    objectManager = new AObjectManager();

    // Create a camera
    mainCamera = objectManager->CreateObject();
    ATransform* trans = new ATransform();
    trans->SetPosition( glm::vec3(1.0f, 0.0f, 2.0f) );
    mainCamera->AddComponent(trans);

    ACamera* camera = new ACamera();
    renderer->SetCamera(camera);
    mainCamera->AddComponent(camera); 
    
    CameraController *cameraController = new CameraController();
    mainCamera->AddComponent(cameraController);

    ACube* floor = objectManager->CreateCube();
    floor->GetComponent<ATransform>()->SetPosition(glm::vec3(0.0f, -1.0f, 0.0f));
    floor->GetComponent<ATransform>()->SetScale(glm::vec3(10.0f, 1.0f, 10.0f));
    floor->GetComponent<AMeshComponent>()->material.SetDiffuseColor(glm::vec3( 0.647059f, 0.164706f, 0.164706f));

    // brown color in rgb?
    // 0.647059, 0.164706, 0.164706

    ACube* cube = objectManager->CreateCube();
    //cube->AddComponent( new TestMovement() );
    cube->GetComponent<ATransform>()->SetPosition(glm::vec3(1.0f, 0.0f, 0.0f));
    cube->GetComponent<AMeshComponent>()->material.SetDiffuseColor(glm::vec3(1.0f, 0.0f, 0.0f));

    ACube* cube2 = objectManager->CreateCube();
    cube2->GetComponent<ATransform>()->SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
    cube2->GetComponent<AMeshComponent>()->material.SetDiffuseColor(glm::vec3(0.0f, 0.0f, 1.0f));
}

AMaster::~AMaster()
{
    glfwTerminate();
    delete renderer;
    delete objectManager;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AMaster::MainLoop()
{
    while (!glfwWindowShouldClose(renderer->window))
    {
        Update();
        Render();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AMaster::PreStart()
{
    objectManager->PreStart();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AMaster::Start()
{
    objectManager->Start();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AMaster::Update()
{
    Time::UpdateTime();
    objectManager->Update();
    
    float elapsedTime = Time::elapsedTime;

    if (elapsedTime >= printTime)
    {
        Time::PrintTime();
        printTime = elapsedTime + 0.5f;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AMaster::SecondUpdate()
{
    objectManager->SecondUpdate();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AMaster::Render()
{   
    renderer->Render();
    objectManager->Render();

    // Swap the front and back buffers
    glfwSwapBuffers(renderer->window);

    // Poll for and process events
    glfwPollEvents();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
