#pragma once

#include <vector>

class AObject;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AObjectManager {
public:
    AObjectManager();
    ~AObjectManager();

    void PreStart();
    void Start();
    void Update();
    void SecondUpdate();
    void Render();

    AObject* CreateObject();
    void DestroyObject(AObject* object);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

private:
    std::vector<AObject*> objects;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
