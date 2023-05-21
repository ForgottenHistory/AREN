#pragma once
#include "glmpch.h"

#include "acomponent.h"

class CameraController : public Component
{
public:
    CameraController(float _speed = 2.5f, float _sensitivity = 0.1f);

    void Update() override;

private:
    float speed = 2.5f;
    float sensitivity = 0.1f;

    double lastMouseX = 0.0;
    double lastMouseY = 0.0;
    bool firstMouse = true;
};