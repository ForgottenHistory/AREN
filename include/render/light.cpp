#include "light.h"
#include "aobject.h"
#include "amaster.h"
#include "arenderer.h"

ADirectionalLight::ADirectionalLight(AVec3 _diffuse, AVec3 _ambient, AVec3 _specular)
{
    diffuse = _diffuse;
    ambient = _ambient;
    specular = _specular;
}

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

    ARenderer &renderer = ARenderer::GetInstance();
    renderer.SetShaderUniform(renderer.shaderProgram, "u_Sun.position", AVec3(transform->GetPosition()));
    renderer.SetShaderUniform(renderer.shaderProgram, "u_Sun.ambient", ambient);
    renderer.SetShaderUniform(renderer.shaderProgram, "u_Sun.diffuse", diffuse);
    renderer.SetShaderUniform(renderer.shaderProgram, "u_Sun.specular", specular);
}
