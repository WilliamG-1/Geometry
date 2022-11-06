#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexArrayObject
{
public:
    VertexArrayObject();
    ~VertexArrayObject();
    void bind();
    void init();
    void init_VBO(float* data, int number_of_elements, unsigned int location, unsigned int count, unsigned int stride, int offset);
    void init_EBO(unsigned int* data, int number_of_elements);
    void set_vertex_attrib_pointer(unsigned int location, unsigned int count, unsigned int stride, int offset);
     float vertices[9] = {
         -0.5f, -0.5f, 0.0f, // left  
          0.5f, -0.5f, 0.0f, // right 
          0.0f,  0.5f, 0.0f  // top   
    }; 
private:
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
};
