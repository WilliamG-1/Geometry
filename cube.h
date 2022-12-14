#pragma once
#include "shape3D.h"
#include "texture.h"

class Cube : public Shape3D
{
public:
    Cube(float s_width);
    float get_number_of_indices() const {return 36;}
    
    void bind_vao();
private:
    //Texture texture;
    float sideLength;
};