#include "aobjectmanager.h"
#include "aobject.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AObjectManager::AObjectManager()
{
}
AObjectManager::~AObjectManager()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AObjectManager::PreStart()
{
    for( int objectIndex = 0; objectIndex < objects.size(); objectIndex++ )
    {
        objects[objectIndex]->PreStart();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AObjectManager::Start()
{
    for( int objectIndex = 0; objectIndex < objects.size(); objectIndex++ )
    {
        objects[objectIndex]->Start();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AObjectManager::Update()
{
    // Update components
    for( int objectIndex = 0; objectIndex < objects.size(); objectIndex++ )
    {
        objects[objectIndex]->UpdateComponents();
    }

    // Update objects
    for( int objectIndex = 0; objectIndex < objects.size(); objectIndex++ )
    {
        objects[objectIndex]->Update();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AObjectManager::SecondUpdate()
{
    for( int objectIndex = 0; objectIndex < objects.size(); objectIndex++ )
    {
        objects[objectIndex]->SecondUpdate();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AObjectManager::Render()
{   
    // Render components
    for( int objectIndex = 0; objectIndex < objects.size(); objectIndex++ )
    {
        objects[objectIndex]->RenderComponents();
    }

    // Render objects
    for( int objectIndex = 0; objectIndex < objects.size(); objectIndex++ )
    {
        objects[objectIndex]->Render();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AObject* AObjectManager::CreateObject()
{
    AObject* newObj = new AObject();
    objects.push_back(newObj);

    return newObj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ACube* AObjectManager::CreateCube()
{
    ACube* newObj = new ACube();
    objects.push_back(newObj);

    return newObj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AObjectManager::DestroyObject(AObject *object)
{
    for( int objectIndex = 0; objectIndex < objects.size(); objectIndex++ )
    {
        if( objects[objectIndex] == object )
        {
            objects.erase(objects.begin() + objectIndex);
            break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
