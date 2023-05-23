#include "aobject.h"
#include "amaster.h"

#include "render/ashadermanager.h"
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

    AShaderManager* shaderManager = AMaster::GetInstance().shaderManager;
    GLuint shaderProgram = 6;

    shaderManager->SetShaderUniform(shaderProgram, "u_Sun.position", AVec3(transform->GetPosition()));
    shaderManager->SetShaderUniform(shaderProgram, "u_Sun.ambient", ambient);
    shaderManager->SetShaderUniform(shaderProgram, "u_Sun.diffuse", diffuse);
    shaderManager->SetShaderUniform(shaderProgram, "u_Sun.specular", specular);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
