#include "amanager.h"
#include "aobject.h"

#define STB_IMAGE_IMPLEMENTATION
#include "imported/stb_image.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AObjectManager::AObjectManager()
{
}
AObjectManager::~AObjectManager()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AObjectManager::PreStart()
{
    for( int objectIndex = 0; objectIndex < objects.size(); objectIndex++ )
    {
        objects[objectIndex]->PreStart();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AObjectManager::Start()
{
    for( int objectIndex = 0; objectIndex < objects.size(); objectIndex++ )
    {
        objects[objectIndex]->Start();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AObjectManager::Update()
{
    // Update components
    for( int objectIndex = 0; objectIndex < objects.size(); objectIndex++ )
    {
        objects[objectIndex]->UpdateComponents();
    }

    // Update objects
    for( int objectIndex = 0; objectIndex < objects.size(); objectIndex++ )
    {
        objects[objectIndex]->Update();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AObjectManager::SecondUpdate()
{
    for( int objectIndex = 0; objectIndex < objects.size(); objectIndex++ )
    {
        objects[objectIndex]->SecondUpdate();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AObjectManager::Render()
{   
    // Render components
    for( int objectIndex = 0; objectIndex < objects.size(); objectIndex++ )
    {
        objects[objectIndex]->RenderComponents();
    }

    // Render objects
    for( int objectIndex = 0; objectIndex < objects.size(); objectIndex++ )
    {
        objects[objectIndex]->Render();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AObject* AObjectManager::CreateObject()
{
    AObject* newObj = new AObject();
    objects.push_back(newObj);

    return newObj;
}

ACube* AObjectManager::CreateCube()
{
    ACube* newObj = new ACube();
    objects.push_back(newObj);

    return newObj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AObjectManager::DestroyObject(AObject *object)
{
    for( int objectIndex = 0; objectIndex < objects.size(); objectIndex++ )
    {
        if( objects[objectIndex] == object )
        {
            objects.erase(objects.begin() + objectIndex);
            break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::unordered_map<std::string, GLuint> TextureManager::textures;

GLuint TextureManager::LoadTexture(const std::string& filePath, const std::string& textureName)
{
    if (textures.find(textureName) != textures.end())
    {
        return textures[textureName];
    }

    int width, height, channels;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

    if (!data)
    {
        std::cerr << "Failed to load texture: " << filePath << std::endl;
        return 0;
    }

    GLuint texture = CreateTexture(width, height, channels, data);
    stbi_image_free(data);

    textures[textureName] = texture;
    return texture;
}

GLuint TextureManager::GetTexture(const std::string& textureName)
{
    if (textures.find(textureName) != textures.end())
    {
        return textures[textureName];
    }

    return 0;
}

void TextureManager::ClearTextures()
{
    for (auto& texture : textures)
    {
        glDeleteTextures(1, &texture.second);
    }
    textures.clear();
}

GLuint TextureManager::CreateTexture(int width, int height, int channels, unsigned char* data)
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