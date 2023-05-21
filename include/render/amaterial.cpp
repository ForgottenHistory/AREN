#include "amaster.h"

#include "render/amaterial.h"
#include "render/arenderer.h"
#include "render/atexturemanager.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AMaterial::AMaterial()
{
    SetShaders(vertexShader, fragmentShader);
    SetDiffuseTexture(diffuseTexture);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AMaterial::SetVertexShader(const std::string &_vertexShader)
{
    ARenderer* renderer = AMaster::GetInstance().renderer;
    vertexShader = _vertexShader;
    shaderProgram = renderer->GetShaderProgram(vertexShader, fragmentShader);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AMaterial::SetFragmentShader(const std::string &_fragmentShader)
{
    ARenderer* renderer = AMaster::GetInstance().renderer;
    fragmentShader = _fragmentShader;
    shaderProgram = renderer->GetShaderProgram(vertexShader, fragmentShader);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AMaterial::SetShaders(const std::string &_vertexShader, const std::string &_fragmentShader)
{
    ARenderer* renderer = AMaster::GetInstance().renderer;
    vertexShader = _vertexShader;
    fragmentShader = _fragmentShader;
    shaderProgram = renderer->GetShaderProgram(vertexShader, fragmentShader);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AMaterial::SetDiffuseTexture(const std::string &_diffuseTexture)
{
    diffuseTexture = _diffuseTexture;
    diffuseTextureID = ATextureManager::GetTexture(diffuseTexture);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
