#include "camera.h"

// Perspective Camera
PerspectiveCamera::PerspectiveCamera(float fov, float screen_width, float screen_height, float near, float far)
    :
    projection(1.0f), view(1.0f), projectionView(1.0f)
{
    position = glm::vec3(0.0f, 0.0f, 9.0f);
    focus = glm::vec3(0.0f, 0.0f, 0.0f);
    direction = glm::normalize(position - focus);

    glm::vec3 u_p(0.0f, 1.0f, 0.0f); // Vector specifying up direction in our world
    right = glm::normalize(glm::cross(direction, u_p));

    up = glm::normalize(glm::cross(up, direction));

    projection = glm::perspective(glm::radians(fov), screen_width/screen_height, near, far);
    view = glm::lookAt(position, focus, glm::vec3(0.0f, 1.0f, 0.0f));

    recalculate();
}

void PerspectiveCamera::moveView(glm::vec3 position)
{
    this->position = position;
    focus = glm::vec3(position.x, position.y, 0.0f);
    view = glm::lookAt(position, focus, glm::vec3(0.0f, 1.0f, 0.0f));
    recalculate();
}
void PerspectiveCamera::recalculate()
{
    projectionView = projection * view;
}




// OrthoGrapic Camera
OrthographicCamera::OrthographicCamera(float screen_width, float screen_height)
    :
    projection(1.0f), view(1.0f), projectionView(1.0f)
{

    projection = glm::ortho(0.0f, screen_width, 0.0f, screen_height);
    recalculate();
}

void OrthographicCamera::moveView(glm::vec3 position)
{
    view = glm::inverse(glm::translate(glm::mat4(1.0f), position));
    recalculate();
}

void OrthographicCamera::recalculate()
{
    projectionView = projection * view;
}