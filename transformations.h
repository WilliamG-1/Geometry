#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "shape2D.h"
class Transformations
{
public:
    static void translate(glm::mat4& model, glm::vec3(position));
    static void rotate2D(glm::mat4& model, Shape2D& shape, float width, float degrees);

    static void translate3D(glm::mat4& model, float xTranslate, float yTranslate, float zTranslate);
    static void rotate3D(glm::mat4& model, float xRotations, float yRotation, float zRotation, glm::vec3 axes);
    static void scale(glm::mat4& model, Shape2D& shape, float width, float scalar);
private:
};