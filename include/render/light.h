#pragma once
#include "glmpch.h"
#include "acomponent.h"

class ARenderer;
class ADirectionalLight : public Component
{
public:

    ADirectionalLight(glm::vec3 _diffuse, glm::vec3 _ambient, glm::vec3 _specular);

    void Render() override;

    glm::vec3 diffuse;
    glm::vec3 ambient;
    glm::vec3 specular;

    glm::vec3 GetDirection() { return transform->GetForward(); }

private:
    ATransform* transform = nullptr;
    ARenderer* renderer = nullptr;
};