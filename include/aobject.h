#pragma once

#include <unordered_map>
#include <typeindex>
#include <acomponent.h>
#include <string>
#include "math/AVec3.h"

class AObject
{
public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename T>
    T* AddComponent(T *component)
    {
        components[typeid(T)] = component;
        component->SetOwner(this);
        return component;
    }

    template <typename T>
    T *GetComponent()
    {
        auto it = components.find(typeid(T));
        if (it != components.end())
        {
            return static_cast<T *>(it->second);
        }
        return nullptr;
    }

    void UpdateComponents()
    {
        for (auto &it : components)
        {
            it.second->Update();
        }
    }

        void RenderComponents()
    {
        for (auto &it : components)
        {
            it.second->Render();
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    virtual void PreStart() {}
    virtual void Start() {}
    virtual void Update() {}
    virtual void SecondUpdate() {}
    virtual void Render() {}

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::unordered_map<std::type_index, Component *> components;
    std::string name = "Object";

protected:
    ATransform *transform = nullptr;

    std::vector<AVec3> CalculateNormals(const std::vector<AVec3>& vertices, const std::vector<unsigned int>& indices);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ACube : public AObject
{
public:
    ACube();
    ~ACube();

    // Override AObject's virtual functions as needed
    void PreStart() override;
    void Start() override;
    void Update() override;
    void SecondUpdate() override;
    void Render() override;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ASkybox : public AObject
{
public:
    ASkybox();
    ~ASkybox();

    // Override AObject's virtual functions as needed
    void Render() override;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
