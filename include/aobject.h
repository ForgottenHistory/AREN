#pragma once

#include <unordered_map>
#include <typeindex>
#include <acomponent.h>
#include <string>

class AObject
{
public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename T>
    void AddComponent(T *component)
    {
        components[typeid(T)] = component;
        std::cout << "Set owner component " << this << std::endl;
        component->SetOwner(this);
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
