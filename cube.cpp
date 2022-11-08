#include "cube.h"

Cube::Cube(float s_width)
{
    sideLength = s_width; // <-- Can you be less confusing?? Lol
    float half_side = sideLength/2;
    float vertices[24] = {
        // Front face
        -half_side, -half_side, 0,  // Bottom Left  (0)
        -half_side,  half_side, 0,  // Top Left     (1)
         half_side, -half_side, 0,  // Bottom Right (2)
         half_side,  half_side, 0,  // Top Right    (3)

         // Back Face 
        -half_side, -half_side, -sideLength,  // Bottom Left  (4)
        -half_side,  half_side, -sideLength,  // Top Left     (5)
         half_side, -half_side, -sideLength,  // Bottom Right (6)
         half_side,  half_side, -sideLength,  // Top Right    (7)
    };

    unsigned int indices[] = {
        0, 1, 2,   1, 2, 3, // Front Face
        3, 2, 6,   3, 7, 6, // Right Face
        4, 5, 6,   5, 6, 7, // Back Face
        1, 5, 4,   0, 1, 4, // Left Face
        1, 3, 5,   3, 5, 7, // Top Face
        0, 2, 4,   2, 4, 6  // Bottom Face
    };
    vao.init_VBO(vertices, 24, 0, 3, 3, 0);
    vao.init_EBO(indices, 36);
}   

void Cube::bind_vao()
{
    vao.bind();
}