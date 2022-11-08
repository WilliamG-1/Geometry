#include "square.h"
#include <iostream>
#include "transformations.h"

Square::Square(float in_x, float in_y, float in_side, bool normalized_coords, float z)
{
    float vertices[12] = {
        -0.5f, -0.5f, z, // Bottom Left  (0)
        -0.5f,  0.5f, z, // Top Left     (1)
         0.5f, -0.5f, z, // Bottom Right (2)
         0.5f,  0.5f, z  // Top Right    (3)

    };
    std::cout << "Square!" << std::endl;
    x = in_x;
    y = in_y;
    side = in_side;

    if (!normalized_coords)
    {
         // Bottom Left
        vertices[0] = x;
        vertices[1] = y;
        vertices[2] = 0.0f;
        // Top Left
        vertices[3] = x;
        vertices[4] = y + side;
        vertices[5] = 0.0f;
        // Bottom Right
        vertices[6] = x + side;
        vertices[7] = y;
        vertices[8] = 0.0f;
        // Top Right 
        vertices[9] = x + side;
        vertices[10] = y + side;
        vertices[11] = 0.0f;
    }
    // Init buffer objects
    vao.init_VBO(vertices, 12, 0, 3, 3, 0);
    vao.init_EBO(indices, 6);
    b_ebo = true;
    ebo_indices = 6;
}

void Square::bind_vao()
{
    vao.bind();
}

