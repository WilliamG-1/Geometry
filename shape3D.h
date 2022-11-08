#pragma once
#include <glm/glm.hpp>
#include "vertexArrayObject.h"

class Shape3D
{
public:
    Shape3D();
    float get_x() const {return x;}
    float get_y() const {return y;}
    float get_z() const {return z;}

    virtual float get_number_of_indices() const = 0;
    virtual void bind_vao() = 0;
    glm::mat4& get_model_matrix() {return model;}

protected:
    float x;
    float y;
    float z;

    VertexArrayObject vao;
    glm::mat4 model;
};