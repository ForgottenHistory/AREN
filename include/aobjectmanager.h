#pragma once
#include "glad/glad.h"
#include "glfw/glfw3.h"
#include <vector>
#include <string>
#include <unordered_map>

class AObject;
class ACube;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AObjectManager {
public:
    // Static method to get the singleton instance
    static AObjectManager& GetInstance()
    {
        static AObjectManager instance; // Only created once
        return instance;
    }

    ~AObjectManager();

    void PreStart();
    void Start();
    void Update();
    void SecondUpdate();
    void Render();

    AObject* CreateObject();
    ACube* CreateCube();
    void DestroyObject(AObject* object);
    
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

private:
    AObjectManager();
    std::vector<AObject*> objects;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
