#include "transformations.h"

void Transformations::rotate2D(glm::mat4& model, Shape2D& shape, float width, float degrees)
{
    model = glm::translate(glm::mat4(1.0f), glm::vec3(shape.get_x() + width/2, shape.get_y() + width/2, 0.0f));
    model = glm::rotate(model, glm::radians(degrees), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(-shape.get_x() - width/2, -shape.get_y() - width/2, 0.0f));
}

void Transformations::scale(glm::mat4& model, Shape2D& shape, float width, float scalar)
{
    model = glm::translate(glm::mat4(1.0f), glm::vec3(shape.get_x() + width/2, shape.get_y() + width/2, 0.0f));
    model = glm::scale(model, glm::vec3(scalar, scalar, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(-(shape.get_x() + width/2), -(shape.get_y() + width/2), 0.0f));
}


void Transformations::translate3D(glm::mat4& model, float xTranslate, float yTranslate, float zTranslate)
{
    model = glm::translate(model, glm::vec3(xTranslate, yTranslate, zTranslate));
}

void Transformations::rotate3D(glm::mat4& model, float xRotation, float yRotation, float zRotation, glm::vec3 axes)
{
   
    model = glm::rotate(model, glm::radians(xRotation), glm::vec3(axes.x, 0.0f, 0.0f)) *  
            glm::rotate(glm::mat4(1.0f), glm::radians(yRotation), glm::vec3(0.0f, axes.y, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(zRotation), glm::vec3(0.0f, 0.0f, axes.z));
}