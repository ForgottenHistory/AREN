#include "aobject.h"
#include "amaster.h"

#include "render/arenderer.h"
#include "render/light.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADirectionalLight::ADirectionalLight(AVec3 _diffuse, AVec3 _ambient, AVec3 _specular)
{
    diffuse = _diffuse;
    ambient = _ambient;
    specular = _specular;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ADirectionalLight::Render()
{
    if (transform == nullptr)
    {
        transform = owner->GetComponent<ATransform>();
        if (transform == nullptr)
        {
            transform = owner->AddComponent(new ATransform());
        }
    }

    ARenderer* renderer = AMaster::GetInstance().renderer;
    GLuint shaderProgram = renderer->shaderProgram;

    renderer->SetShaderUniform(shaderProgram, "u_Sun.position", AVec3(transform->GetPosition()));
    renderer->SetShaderUniform(shaderProgram, "u_Sun.ambient", ambient);
    renderer->SetShaderUniform(shaderProgram, "u_Sun.diffuse", diffuse);
    renderer->SetShaderUniform(shaderProgram, "u_Sun.specular", specular);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
