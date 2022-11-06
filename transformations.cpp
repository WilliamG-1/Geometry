#include "transformations.h"

void Transformations::rotate(glm::mat4& model, Shape2D& shape, float width, float degrees)
{
    model = glm::translate(glm::mat4(1.0f), glm::vec3(shape.get_x() + width/2, shape.get_y() + width/2, 0.0f));
    model = glm::rotate(model, glm::radians(degrees), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(-shape.get_x() - width/2, -shape.get_y() - width/2, 0.0f));
}

void Transformations::scale(glm::mat4& model, Shape2D& shape, float width, float scalar)
{
    model = glm::translate(glm::mat4(1.0f), glm::vec3(shape.get_x() + width/2, shape.get_y() + width/2, 0.0f));
    model = glm::scale(model, glm::vec3(scalar, scalar, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(-(shape.get_x() + width/2), -(shape.get_y() + width/2), 0.0f));
}