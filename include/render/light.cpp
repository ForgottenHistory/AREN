#include "light.h"
#include "aobject.h"
#include "amaster.h"
#include "arenderer.h"

ADirectionalLight::ADirectionalLight(glm::vec3 _diffuse, glm::vec3 _ambient, glm::vec3 _specular)
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

    ARenderer& renderer = ARenderer::GetInstance();
    renderer.SetShaderUniform("u_Sun.position", transform->GetPosition());
    renderer.SetShaderUniform("u_Sun.ambient", ambient);
    renderer.SetShaderUniform("u_Sun.diffuse", diffuse);
    renderer.SetShaderUniform("u_Sun.specular", specular);
}
