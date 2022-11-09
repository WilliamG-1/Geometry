#include "vertexArrayObject.h"
#include <iostream>
VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
}

void VertexArrayObject::init_VBO(float* data, int number_of_elements, unsigned int location, unsigned int count, unsigned int stride, int offset)
{
    
    //glGenBuffers(1, &ebo);
 
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * number_of_elements, data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(location);

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

void VertexArrayObject::bind()
{
    glBindVertexArray(vao);
}

VertexArrayObject::~VertexArrayObject()
{
    glDeleteVertexArrays(1, &vao);
}
