#include "amaster.h"

#include "render/amaterial.h"
#include "render/ashadermanager.h"
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
    AShaderManager* shaderManager = AMaster::GetInstance().shaderManager;
    vertexShader = _vertexShader;
    shaderProgram = shaderManager->GetShaderProgram(vertexShader, fragmentShader);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AMaterial::SetFragmentShader(const std::string &_fragmentShader)
{
    AShaderManager* shaderManager = AMaster::GetInstance().shaderManager;
    fragmentShader = _fragmentShader;
    shaderProgram = shaderManager->GetShaderProgram(vertexShader, fragmentShader);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AMaterial::SetShaders(const std::string &_vertexShader, const std::string &_fragmentShader)
{
    AShaderManager* shaderManager = AMaster::GetInstance().shaderManager;
    vertexShader = _vertexShader;
    fragmentShader = _fragmentShader;
    shaderProgram = shaderManager->GetShaderProgram(vertexShader, fragmentShader);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AMaterial::SetDiffuseTexture(const std::string &_diffuseTexture)
{
    diffuseTexture = _diffuseTexture;
    diffuseTextureID = ATextureManager::GetTexture(diffuseTexture);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
