#pragma once
#include "vertexArrayObject.h"
#include <glm/glm.hpp>
class Shape2D
{
public:
    Shape2D();

    float get_x() const {return x;}
    float get_y() const {return y;}
    float get_area();
    
    virtual void bind_vao() = 0;
    glm::mat4& get_model() {return model;}

    int get_ebo_indices() const {return ebo_indices;}

    bool uses_ebo() const {return b_ebo;}
protected:
    VertexArrayObject vao;
    glm::mat4 model;

    float x;
    float y;
    bool b_ebo = false;
    int ebo_indices = 0;
};