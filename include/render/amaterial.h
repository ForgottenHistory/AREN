#pragma once
#include <glmpch.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <string>

#include "math/AVec3.h"

class AMaterial
{
public:
    AMaterial();
    ~AMaterial() {}

    void SetDiffuseColor(const AVec3 &_diffuseColor) { diffuseColor = _diffuseColor; }
    const AVec3 &GetDiffuseColor() const { return diffuseColor; }

    void SetSpecularColor(const AVec3 &_specularColor) { specularColor = _specularColor; }
    const AVec3 &GetSpecularColor() const { return specularColor; }

    void SetShininess(const float _shininess) { shininess = _shininess; }
    const float GetShininess() const { return shininess; }

    void SetVertexShader(const std::string &_vertexShader);
    const std::string &GetVertexShader() const { return vertexShader; }

    void SetFragmentShader(const std::string &_fragmentShader);
    const std::string &GetFragmentShader() const { return fragmentShader; }

    void SetShaders(const std::string &_vertexShader, const std::string &_fragmentShader);

    void SetDiffuseTexture(const std::string &_diffuseTexture);
    const std::string &GetDiffuseTexture() const { return diffuseTexture; }
    GLuint GetDiffuseTextureID() const { return diffuseTextureID; }

    GLuint GetShaderProgram() const { return shaderProgram; }

private:
    AVec3 diffuseColor = AVec3(1.0f);
    AVec3 specularColor = AVec3(0.0f);

    std::string diffuseTexture = "default_texture.jpg";
    GLuint diffuseTextureID = 0;

    std::string vertexShader = "vertex_shader";
    std::string fragmentShader = "fragment_shader";
    GLuint shaderProgram = 0;

    float shininess = 1.0f;
};