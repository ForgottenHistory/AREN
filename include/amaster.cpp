#include "amaster.h"
#include "aobject.h"
#include "aobjectmanager.h"
#include "time.h"
#include "acomponent.h"
#include "acolor.h"

#include "render/atexturemanager.h"
#include "render/amaterialmanager.h"
#include "render/arenderer.h"
#include "render/light.h"
#include "render/ashadermanager.h"

#include "components/movewithtime.h"
#include "components/cameracontroller.h"

#include "math/AVec3.h"
#include "debug/test.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AMaster::AMaster()
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // CREATE MANAGERS
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    objectManager = new AObjectManager();
    colorManager = new AColorManager();
    renderer = new ARenderer();
    textureManager = new ATextureManager();
    materialManager = new AMaterialManager();
    shaderManager = new AShaderManager();
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AMaster::~AMaster()
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    delete objectManager;
    delete colorManager;
    delete renderer;
    delete textureManager;
    delete materialManager;
    delete shaderManager;

    glfwTerminate();
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AMaster::Initialize()
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // INITIALIZE MANAGERS
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    renderer->Initialize();
    shaderManager->Initialize();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // CREATE SKYBOX
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // AObject *skybox = objectManager.CreateObject();
    // skybox->name = "Skybox";
    // skybox->AddComponent(new ASkyboxComponent());

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // CREATE CAMERA
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    mainCamera = objectManager->CreateObject();
    ATransform *cameraTrans = new ATransform();
    cameraTrans->SetPosition(glm::vec3(1.0f, 0.0f, 2.0f));
    mainCamera->AddComponent(cameraTrans);

    ACamera *camera = new ACamera();
    renderer->SetCamera(camera);
    mainCamera->AddComponent(camera);

    CameraController *cameraController = new CameraController();
    mainCamera->AddComponent(cameraController);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    CreateStartObjects();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

void AMaster::CreateStartObjects()
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // CREATE LIGHTS
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Set directional light values
    glm::vec3 sunPosition = glm::vec3(20.0f, 20.0f, 20.0f);
    AVec3 sunDiffuse = AVec3(1.0f, 0.9f, 0.7f);
    AVec3 sunAmbient = AVec3(0.1f, 0.1f, 0.1f);
    AVec3 sunSpecular = AVec3(1.0f, 1.0f, 1.0f);

    // Uncomment to use matte light
    // sunDiffuse = colorManager.GetColor(ColorManager::WHITE);
    // sunAmbient = colorManager.GetColor(ColorManager::WHITE);
    // sunSpecular = colorManager.GetColor(ColorManager::WHITE);

    AObject *light = objectManager->CreateObject();
    ADirectionalLight *directionalLight = new ADirectionalLight(sunDiffuse,
                                                                sunAmbient,
                                                                sunSpecular);
    light->AddComponent(directionalLight);

    ATransform *sunTrans = new ATransform();
    sunTrans->SetPosition(sunPosition);
    light->AddComponent(sunTrans);

    MoveWithTime *moveWithTime = new MoveWithTime(MoveWithTime::MoveType::SINTIME);
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
    AVec3 color = colorManager->GetColor(COLORS::BLUE);
    floor->GetComponent<AMeshComponent>()->material->SetDiffuseColor(color);
    floor->GetComponent<AMeshComponent>()->material->SetShaders("vertex_shader", "fragment_shader");

    ACube *cube = objectManager->CreateCube();
    cube->AddComponent( new TestMovement() );
    cube->GetComponent<ATransform>()->SetPosition(glm::vec3(1.0f, 0.0f, 0.0f));
    //cube->GetComponent<AMeshComponent>()->material->SetDiffuseColor(colorManager->GetColor(COLORS::RED));
    cube->GetComponent<AMeshComponent>()->material->SetDiffuseTexture("bricks.jpg");
    //cube->GetComponent<AMeshComponent>()->material->SetShaders("vertex_shader", "fragment_simple_shader");
    cube->GetComponent<AMeshComponent>()->material->SetShaders("vertex_shader", "fragment_shader");

    ACube *cube2 = objectManager->CreateCube();
    cube2->GetComponent<ATransform>()->SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
    // cube2->GetComponent<AMeshComponent>()->material->SetDiffuseColor(colorManager.GetColor(ColorManager::BLUE));
    cube2->GetComponent<AMeshComponent>()->material->SetDiffuseTexture("bricks.jpg");
    cube2->GetComponent<AMeshComponent>()->material->SetShaders("vertex_shader", "fragment_normals_shader");

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
