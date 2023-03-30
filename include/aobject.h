#pragma once

#include <unordered_map>
#include <typeindex>
#include <acomponent.h>

class AObject {
public:

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    template<typename T>
    void AddComponent(T* component ) {
        components[typeid(T)] = component;
        component->SetOwner(this);
    }

    template<typename T>
    T* GetComponent() {
        auto it = components.find(typeid(T));
        if (it != components.end()) {
            return static_cast<T*>(it->second);
        }
        return nullptr;
    }

    void UpdateComponents() {
        for (auto& it : components) {
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

protected:
    std::unordered_map<std::type_index, Component*> components;

    ATransform* transform = nullptr;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
