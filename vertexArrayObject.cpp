#include "vertexArrayObject.h"
#include <iostream>
VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
}

void VertexArrayObject::init_VBO(float* data, int number_of_elements, unsigned int location, unsigned int count_per_vertices, unsigned int stride, int offset)
{
    
    //glGenBuffers(1, &ebo);
 
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * number_of_elements, data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, count_per_vertices, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(location);

    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    //glBindVertexArray(0);
    //glDeleteBuffers(1, &vbo);
}

void VertexArrayObject::init_EBO(unsigned int* data, int number_of_elements)
{
    glBindVertexArray(vao);

    glGenBuffers(1, &ebo);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * number_of_elements, data, GL_STATIC_DRAW);

}

void VertexArrayObject::set_vertex_attrib_pointer(float* data, int number_of_elements, unsigned int location, unsigned int count, unsigned int stride, int offset)
{
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * number_of_elements, data, GL_STATIC_DRAW);

    glVertexAttribPointer(location, count, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(location);

}



void VertexArrayObject::bind()
{
    glBindVertexArray(vao);
}

VertexArrayObject::~VertexArrayObject()
{
    glDeleteVertexArrays(1, &vao);
}
