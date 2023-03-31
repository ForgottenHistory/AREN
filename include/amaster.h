#pragma once
#include <vector>

class AObjectManager;
class ARenderer;
class AObject;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AMaster
{
public:

    // Static method to get the singleton instance
    static AMaster& GetInstance()
    {
        static AMaster instance; // Only created once
        return instance;
    }

    ~AMaster();

    void MainLoop();
    void PreStart();
    void Start();
    void Update();
    void SecondUpdate();
    void Render();

    ARenderer* GetRenderer() { return renderer; }
    AObjectManager* GetObjectManager() { return objectManager; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

private:
    AMaster();

    ARenderer* renderer;
    AObjectManager* objectManager;

    AObject* mainCamera;

    float printTime = 0.5f;

    // Private copy constructor and assignment operator to prevent copying
    AMaster(const AMaster&) = delete;
    AMaster& operator=(const AMaster&) = delete;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
