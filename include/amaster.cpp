#include <amaster.h>
#include <aobject.h>
#include <amanager.h>
#include <render/arenderer.h>
#include <time.h>
#include "acomponent.h"
#include "render/testrenderer.h"
#include "acolor.h"

#include "render/light.h"
#include "components/movewithtime.h"
#include "components/cameracontroller.h"

#include "debug/test.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AMaster::AMaster() : renderer(ARenderer::GetInstance())
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Create a test renderer
    // TestRenderer* testRenderer = new TestRenderer();
    // testRenderer->Main();

    objectManager = new AObjectManager();
    ColorManager &colorManager = ColorManager::GetInstance();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // CREATE CAMERA
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    mainCamera = objectManager->CreateObject();
    ATransform *cameraTrans = new ATransform();
    cameraTrans->SetPosition(glm::vec3(1.0f, 0.0f, 2.0f));
    mainCamera->AddComponent(cameraTrans);

    ACamera *camera = new ACamera();
    renderer.SetCamera(camera);
    mainCamera->AddComponent(camera);

    CameraController *cameraController = new CameraController();
    mainCamera->AddComponent(cameraController);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // CREATE LIGHTS
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Set directional light values
    glm::vec3 sunPosition = glm::vec3(20.0f, 20.0f, 20.0f);
    glm::vec3 sunDiffuse = glm::vec3( 1.0f, 0.9f, 0.7f);
    glm::vec3 sunAmbient = glm::vec3( 0.1f, 0.1f, 0.1f);
    glm::vec3 sunSpecular = glm::vec3( 1.0f, 1.0f, 1.0f);

    // Uncomment to use matte light
    //sunDiffuse = colorManager.GetColor(ColorManager::WHITE);
    //sunAmbient = colorManager.GetColor(ColorManager::WHITE);
    //sunSpecular = colorManager.GetColor(ColorManager::WHITE);

    AObject *light = objectManager->CreateObject();
    ADirectionalLight *directionalLight = new ADirectionalLight(sunDiffuse,
                                                                sunAmbient,
                                                                sunSpecular);
    light->AddComponent(directionalLight);

    ATransform *sunTrans = new ATransform();
    sunTrans->SetPosition(sunPosition);
    light->AddComponent(sunTrans);

    MoveWithTime* moveWithTime = new MoveWithTime( MoveWithTime::MoveType::SINTIME );
    moveWithTime->lockX = true;
    moveWithTime->lockY = false;
    moveWithTime->lockZ = true;
    moveWithTime->speed = 0.5f;
    moveWithTime->amplitude = 20.0f;
    light->AddComponent(moveWithTime);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // CREATE CUBES
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ACube *floor = objectManager->CreateCube();
    floor->GetComponent<ATransform>()->SetPosition(glm::vec3(0.0f, -1.0f, 0.0f));
    floor->GetComponent<ATransform>()->SetScale(glm::vec3(10.0f, 1.0f, 10.0f));
    floor->GetComponent<AMeshComponent>()->material->SetDiffuseColor(colorManager.GetColor(ColorManager::BROWN));
    floor->GetComponent<AMeshComponent>()->material->SetShaders("vertex_shader_test", "fragment_shader_test");

    ACube *cube = objectManager->CreateCube();
    // cube->AddComponent( new TestMovement() );
    cube->GetComponent<ATransform>()->SetPosition(glm::vec3(1.0f, 0.0f, 0.0f));
    //cube->GetComponent<AMeshComponent>()->material->SetDiffuseColor(colorManager.GetColor(ColorManager::RED));
    cube->GetComponent<AMeshComponent>()->material->SetDiffuseTexture("bricks");
    //cube->GetComponent<AMeshComponent>()->material->SetShaders("vertex_shader.glsl", "fragment_simple_shader.glsl");
    cube->GetComponent<AMeshComponent>()->material->SetShaders("vertex_shader_test", "fragment_shader_test");

    ACube *cube2 = objectManager->CreateCube();
    cube2->GetComponent<ATransform>()->SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
    //cube2->GetComponent<AMeshComponent>()->material->SetDiffuseColor(colorManager.GetColor(ColorManager::BLUE));
    cube2->GetComponent<AMeshComponent>()->material->SetDiffuseTexture("bricks");
    cube2->GetComponent<AMeshComponent>()->material->SetShaders("vertex_shader_test", "fragment_normals_shader");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AMaster::~AMaster()
{
    glfwTerminate();
    delete objectManager;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AMaster::MainLoop()
{
    while (!glfwWindowShouldClose(renderer.window))
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
    renderer.Render();
    objectManager->Render();

    // Swap the front and back buffers
    glfwSwapBuffers(renderer.window);

    // Poll for and process events
    glfwPollEvents();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
