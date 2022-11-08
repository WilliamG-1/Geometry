#include "camera.h"

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

// Perspective Camera
PerspectiveCamera::PerspectiveCamera(float fov, float screen_width, float screen_height, float near, float far)
    :
    projection(1.0f), view(1.0f), projectionView(1.0f)
{
    projection = glm::perspective(glm::radians(fov), screen_width/screen_height, near, far);
    recalculate();
}

void PerspectiveCamera::moveView(glm::vec3 position)
{
    view = glm::translate(glm::mat4(1.0f), position);
    recalculate();
}
void PerspectiveCamera::recalculate()
{
    projectionView = projection * view;
}