#include "shadercontroller.h"
#include "amaster.h"
#include "render/arenderer.h"

ShaderController::ShaderController(float steps)
{
    this->steps = steps;
}

void ShaderController::Update()
{
    window = ARenderer::GetInstance().window;

    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
    {
        value += steps;
        ARenderer::GetInstance().SetShaderUniform("u_Shininess", value);
    }
    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
    {
        value -= steps;
        ARenderer::GetInstance().SetShaderUniform("u_Shininess", value);
    }
}
