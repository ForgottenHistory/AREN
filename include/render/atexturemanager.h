#pragma once
#include <glmpch.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <string>
#include <unordered_map>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ATextureManager {
public:
    // Get the texture object by name
    static GLuint GetTexture(const std::string& textureName);

    // Release all loaded textures
    static void ClearTextures();

private:

    // Load and store a texture from a file
    static GLuint LoadTexture(const std::string& textureName);

    // A map that stores texture objects by their name
    static std::unordered_map<std::string, GLuint> textures;

    // Utility function to create a texture object from image data
    static GLuint CreateTexture(int width, int height, int channels, unsigned char* data);

    // Private copy constructor and assignment operator to prevent copying
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
