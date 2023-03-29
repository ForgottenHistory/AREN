#pragma once

#include <unordered_map>
#include <typeindex>
#include <acomponent.h>

class AObject {
public:
    template<typename T>
    void AddComponent(T* component) {
        components[typeid(T)] = component;
    }

    template<typename T>
    T* GetComponent() {
        auto it = components.find(typeid(T));
        if (it != components.end()) {
            return static_cast<T*>(it->second);
        }
        return nullptr;
    }

private:
    std::unordered_map<std::type_index, Component*> components;
};
