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