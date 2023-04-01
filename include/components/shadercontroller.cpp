#include "shadercontroller.h"
#include "amaster.h"
#include "render/arenderer.h"

ShaderController::ShaderController(float steps)
{
    this->steps = steps;
}

void ShaderController::Update()
{
    renderer = AMaster::GetInstance().GetRenderer();
    window = renderer->window;

    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
    {
        value += steps;
        renderer->SetShaderUniform("u_Shininess", value);
    }
    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
    {
        value -= steps;
        renderer->SetShaderUniform("u_Shininess", value);
    }
}
