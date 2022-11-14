#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Texture
{
public:
    Texture(const char* file_path);
    Texture(const char* file_path, unsigned int slot);
    Texture(const char* file_path, unsigned int slot, GLint minFilter, GLint maxFiler, GLint sWrap, GLint tWrap);
    ~Texture();
    
    void bindTexture(unsigned int slot);
private:
    unsigned int textureID;
};