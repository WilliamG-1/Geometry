#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "shape2D.h"
#include "shape3D.h"

struct Material{
    glm::vec3 ambient;
    glm::vec3 diffusion;
    glm::vec3 specular;

    float shininess;
};

class Renderer
{
public:
    Renderer();

    void draw2D(Shader& shader, Shape2D& shape);
    void draw3D(Shader& shader, Shape3D& shape, Material material);
    void draw3D(Shader& shader, Shape3D& shape);
private:

};