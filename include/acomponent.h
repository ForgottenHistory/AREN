#pragma once
#include <iostream>

class Component {
public:
    virtual ~Component() {}

    virtual void Update() = 0;
};

class ExampleComponent : public Component {
public:
    ExampleComponent() { std::cout << "ExampleComponent created" << std::endl; }

    void Update() override {
        // Example code
    }
};
