#include "render/atexturemanager.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "imported/stb_image.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::unordered_map<std::string, GLuint> ATextureManager::textures;

GLuint ATextureManager::LoadTexture(const std::string& textureName)
{
    if (textures.find(textureName) != textures.end())
    {
        return textures[textureName];
    }

    int width, height, channels;
    std::string filePath = "textures/" + textureName;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

    if (!data) {
        std::cerr << "Failed to load texture: " << filePath << std::endl;
        return 0;
    }

    GLuint texture = CreateTexture(width, height, channels, data);
    stbi_image_free(data);

    textures[textureName] = texture;
    return texture;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GLuint ATextureManager::GetTexture(const std::string& textureName)
{
    if (textures.find(textureName) != textures.end())
    {
        return textures[textureName];
    } else {
        return LoadTexture( textureName );
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ATextureManager::ClearTextures()
{
    for (auto& texture : textures)
    {
        glDeleteTextures(1, &texture.second);
    }
    textures.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GLuint ATextureManager::CreateTexture(int width, int height, int channels, unsigned char* data)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}