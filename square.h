#pragma once
#include "shape2D.h"
#include "vertexArrayObject.h"

class Square : public Shape2D
{
public:
    Square(float in_x, float in_y, float in_side, bool normalized_coordinates = false);

    void bind_vao() override;

    float get_area() {return side * side;}
    float get_perimeter() {return side * 4;}

    float get_x() const {return x;}
    float get_y() const {return y;}
    float get_side() const {return side;}

private:
    float vertices[12] = {
        -0.5f, -0.5f, 0.0f, // Bottom Left  (0)
        -0.5f,  0.5f, 0.0f, // Top Left     (1)
         0.5f, -0.5f, 0.0f, // Bottom Right (2)
         0.5f,  0.5f, 0.0f  // Top Right    (3)

    };
    unsigned int indices[6] = {
        0, 1, 2,
        1, 2, 3
    };
    float side;
};