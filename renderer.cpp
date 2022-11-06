#include "renderer.h"

Renderer::Renderer()
{

}

void Renderer::draw2D(Shader& shader, Shape2D& Shape2D)
{
    shader.use_shader();
    Shape2D.bind_vao();
    if(Shape2D.uses_ebo())
    {
        glDrawElements(GL_TRIANGLES, Shape2D.get_ebo_indices(), GL_UNSIGNED_INT, 0);
    }
}