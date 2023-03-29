#pragma once
#include <render/arenderer.h>

class AMaster
{
public:
    AMaster();
    ~AMaster();

    void MainLoop();
    void Update();
    void Render();

private:
    ARenderer* renderer;

    float printTime = 0.5f;
};