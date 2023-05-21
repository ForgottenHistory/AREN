#pragma once
#include <vector>

class ATextureManager;
class AMaterialManager;
class AObjectManager;
class AColorManager;
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

    void Initialize();

    // Main functions
    void MainLoop();
    void PreStart();
    void Start();
    void Update();
    void SecondUpdate();
    void Render();

    void CreateStartObjects();

    // Managers
    ATextureManager* textureManager;
    AMaterialManager* materialManager;
    AObjectManager* objectManager;
    ARenderer* renderer;
    AColorManager* colorManager;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

private:
    AMaster();

    AObject* mainCamera;

    float printTime = 0.5f;

    // Private copy constructor and assignment operator to prevent copying
    AMaster(const AMaster&) = delete;
    AMaster& operator=(const AMaster&) = delete;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
