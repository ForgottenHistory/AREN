#include <amaster.h>
#include <render/arenderer.h>
#include <time.h>
#include <aobject.h>

AMaster::AMaster()
{
    renderer = new ARenderer();

    entities.push_back(new AObject());
    entities[0]->AddComponent(new ExampleComponent());
}

AMaster::~AMaster()
{
    glfwTerminate();
    delete renderer;
}

void AMaster::MainLoop()
{
    while (!glfwWindowShouldClose(renderer->window))
    {
        Update();
        Render();
    }
}

void AMaster::Update()
{
    Time::UpdateTime();
}

void AMaster::Render()
{
    renderer->Render();

    float elapsedTime = Time::elapsedTime;

    if (elapsedTime >= printTime)
    {
        Time::PrintTime();
        printTime = elapsedTime + 0.5f;
    }

    // Swap the front and back buffers
    glfwSwapBuffers(renderer->window);

    // Poll for and process events
    glfwPollEvents();
}