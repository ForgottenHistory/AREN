#pragma once
#include "glad/glad.h"
#include "glfw/glfw3.h"
#include <vector>
#include <string>
#include <unordered_map>

class AObject;
class ACube;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AObjectManager {
public:
    AObjectManager();
    ~AObjectManager();

    void PreStart();
    void Start();
    void Update();
    void SecondUpdate();
    void Render();

    AObject* CreateObject();
    ACube* CreateCube();
    void DestroyObject(AObject* object);
    
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

private:

    std::vector<AObject*> objects;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class TextureManager {
public:
    // Load and store a texture from a file
    static GLuint LoadTexture(const std::string& filePath, const std::string& textureName);

    // Get the texture object by name
    static GLuint GetTexture(const std::string& textureName);

    // Release all loaded textures
    static void ClearTextures();

private:
    // A map that stores texture objects by their name
    static std::unordered_map<std::string, GLuint> textures;

    // Utility function to create a texture object from image data
    static GLuint CreateTexture(int width, int height, int channels, unsigned char* data);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
