#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "shape2D.h"
class Transformations
{
public:
    static void translate(glm::mat4& model, glm::vec3(position));
    static void rotate(glm::mat4& model, Shape2D& shape, float width, float degrees);
    static void scale(glm::mat4& model, Shape2D& shape, float width, float scalar);
private:
};