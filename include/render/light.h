#pragma once
#include "glmpch.h"
#include "acomponent.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ADirectionalLight : public Component
{
public:

    ADirectionalLight(AVec3 _diffuse, AVec3 _ambient, AVec3 _specular);

    void Render() override;

    AVec3 diffuse;
    AVec3 ambient;
    AVec3 specular;

    glm::vec3 GetDirection() { return transform->GetForward(); }

private:
    ATransform* transform = nullptr;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
