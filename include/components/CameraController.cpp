#include "CameraController.h"
#include "render/arenderer.h"
#include "amaster.h"
#include "time.h"
#include "aobject.h"

CameraController::CameraController(float _speed, float _sensitivity)
{
    speed = _speed;
    sensitivity = _sensitivity;
}

void CameraController::Update()
{
    GLFWwindow* window = AMaster::GetInstance().GetRenderer()->window;
    ATransform* transform = owner->GetComponent<ATransform>();

    // Keyboard input
    glm::vec3 movementOffset(0.0f, 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        movementOffset -= transform->GetForward() * speed * Time::deltaTime;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        movementOffset += transform->GetForward() * speed * Time::deltaTime;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        movementOffset += transform->GetRight() * speed * Time::deltaTime;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        movementOffset -= transform->GetRight() * speed * Time::deltaTime;

    glm::vec3 pos = transform->GetPosition();
    pos += movementOffset;
    transform->SetPosition(pos);

    // Handle mouse input
    double mouseX, mouseY;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    glfwGetCursorPos(AMaster::GetInstance().GetRenderer()->window, &mouseX, &mouseY);

    if (firstMouse)
    {
        lastMouseX = mouseX;
        lastMouseY = mouseY;
        firstMouse = false;
    }

    double xOffset = mouseX - lastMouseX;
    double yOffset = lastMouseY - mouseY;
    lastMouseX = mouseX;
    lastMouseY = mouseY;

    xOffset *= sensitivity;
    yOffset *= sensitivity;

    glm::vec3 rotation = transform->GetRotation();
    //rotation.x += (float)yOffset;
    rotation.y -= (float)xOffset;

    // Clamp pitch rotation to prevent camera from flipping

    transform->SetRotation(rotation);
}