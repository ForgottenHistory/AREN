#pragma once
#include "glmpch.h"
#include "acomponent.h"

class ARenderer;
class ShaderController : public Component
{
    
public:
    ShaderController(float steps = 0.2f);

    void Update() override;

private:
    GLFWwindow* window;
    float steps = 0.2f;
    float value = 0.0f;
};