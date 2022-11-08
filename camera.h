#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class PerspectiveCamera
{
public:
    PerspectiveCamera(float fov, float screen_width, float screen_height, float near, float far);
    void moveView(glm::vec3 position);
    void recalculate();

    glm::mat4 get_projection_view_matrix() {return projectionView;}
private:
    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 projectionView;

    glm::vec3 position;     // Position of our camera
    glm::vec3 focus;        // Position that our camera is lookint at
    glm::vec3 direction;    // Direction vector (Note that it points towards our camera, not the focus)
    glm::vec3 right;
    glm::vec3 up;
};


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
