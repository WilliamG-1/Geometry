#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class OrthographicCamera
{
public:
    OrthographicCamera(float screen_width, float screen_height);
    void moveView(glm::vec3 position);
    void recalculate();

    glm::mat4 get_projection_view_matrix() {return projectionView;}
private:
    glm::mat4 projectionView;
    glm::mat4 view;
    glm::mat4 projection;
};

class PerspectiveCamera
{
public:

private:
    glm::mat4 view;

};