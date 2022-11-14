#include "texture.h"
#include <iostream>

Texture::Texture(const char* file_path)
{
    stbi_set_flip_vertically_on_load(true);

    glGenTextures(1, &textureID);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(file_path, &width, &height, &nrChannels, 0);
    std::cout << "Loading from " << file_path << std::endl;

    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    } else std::cout << "Error, unable to load Texture: No data found!" << std::endl;
    
}

Texture::Texture(const char* file_path, unsigned int slot)
{
    stbi_set_flip_vertically_on_load(true);

    glGenTextures(1, &textureID);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(file_path, &width, &height, &nrChannels, 0);
    std::cout << "Loading from " << file_path << std::endl;

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    } else std::cout << "Error, unable to load Texture: No data found!" << std::endl;
}

Texture::Texture(const char* file_path, unsigned int slot, GLint minFilter, GLint maxFiler, GLint sWrap, GLint tWrap)
{
    stbi_set_flip_vertically_on_load(true);

    glGenTextures(1, &textureID);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(file_path, &width, &height, &nrChannels, 0);
    std::cout << "Loading from " << file_path << std::endl;

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFiler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    } else std::cout << "Error, unable to load Texture: No data found!" << std::endl;
}

void Texture::bindTexture(unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureID);
}