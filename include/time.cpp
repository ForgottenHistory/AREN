#include "time.h"
#include <glfw/glfw3.h>
#include <cmath>
#include <iostream>

float Time::time = 0.0f;
float Time::deltaTime = 0.0f;
float Time::sinTime = 0.0f;
float Time::cosTime = 0.0f;
float Time::tanTime = 0.0f;
float Time::elapsedTime = 0.0f;
float Time::currentTime = 0.0f;
float Time::lastTime = 0.0f;

void Time::UpdateTime()
{
    // Calculate elapsed time since last frame
    currentTime = glfwGetTime();
    deltaTime = static_cast<float>(currentTime - lastTime);
    lastTime = currentTime;

    // Update the elapsedTime variable
    elapsedTime += deltaTime;

    // Calculate the offset based on elapsed time
    sinTime = sin(elapsedTime);
    cosTime = cos(elapsedTime);
    tanTime = tan(elapsedTime);
}

void Time::PrintTime()
{
    std::cout << "deltaTime: " << deltaTime << " elapsedTime: " << elapsedTime << std::endl;
}
