#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <random>

#include "shader.h"
#include "vertexArrayObject.h"
#include "renderer.h"
#include "square.h"
#include "cube.h"
#include "camera.h"
#include "transformations.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, PerspectiveCamera& camera);
int randint(int first, int second);
void updateDT();

float phi = 90;
float theta = 90;
float panSpeed = 80;

float dt = 0;
float current = 0;
float last = 0;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Models", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) 
    {
        
        if (key == GLFW_KEY_0 && action == GLFW_PRESS)
        {
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        }
        if (key == GLFW_KEY_1 && action == GLFW_PRESS)
        {
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        }
    });

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shader;
    Shader lightShader;
    shader.init_shaders("shaders/vertex.vert", "shaders/fragment.frag");
    lightShader.init_shaders("shaders/lightVertex.vert", "shaders/lightFragment.frag");
    Renderer renderer;

    PerspectiveCamera p_Camera(45.0f, 800, 600, 0.1f, 90.0f);
    Cube cube(1.0f);
    Cube lightCube(1.0f);
    Transformations::translate3D(lightCube.get_model_matrix(), 2.0f, 0.0f, -7.0f);
    std::vector<Cube> v_Cubes;
    // for (int i = 1; i < 90; i++)
    // {
    //     v_Cubes.push_back(Cube(1.0f));
    //     Transformations::translate3D(v_Cubes[i - 1].get_model_matrix(), randint(-10, 10), randint(-10, 10), randint(-15, 0));
    //     Transformations::rotate3D(v_Cubes[i - 1].get_model_matrix(), i * 10, i * 33, i % 3, glm::vec3(1.0f, 1.0f, 1.0f));
    // }

    shader.setUniformVec3f("u_ObjectColor", 1, 1, 1);
    shader.setUniformVec3fv("u_LightColor", glm::vec3(0.15f, 0.27f, 0.324));
    glEnable(GL_DEPTH_TEST);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window, p_Camera);

        // render
        // ------
        glClearColor(0.2, 0.39f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.setUniformMat4f("u_ViewProjection", p_Camera.get_projection_view_matrix());
        lightShader.setUniformMat4f("u_ViewProjection", p_Camera.get_projection_view_matrix());

        renderer.draw3D(shader, cube);
        renderer.draw3D(lightShader, lightCube);
        // for (Cube& cube : v_Cubes)
        //     renderer.draw3D(shader, cube);
        
        std::printf("Camera: (%.2f, %.2f, %.2f)\n", p_Camera.get_position().x, p_Camera.get_position().y, p_Camera.get_position().z);

        updateDT();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window, PerspectiveCamera& camera)
{
    // Camera movement 
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Camera Movement
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.move(CameraDirection::LEFT, dt);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.move(CameraDirection::RIGHT, dt);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.move(CameraDirection::FORWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.move(CameraDirection::BACKWARD, dt);   
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.move(CameraDirection::UP, dt);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.move(CameraDirection::DOWN, dt);

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        theta += panSpeed *  dt;
        camera.euler_angle(phi, theta);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        theta -= panSpeed * dt;
        camera.euler_angle(phi, theta);
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        phi -= panSpeed * dt;
        if (phi > 179)
            phi = 179; 
        camera.euler_angle(phi, theta); 
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        phi += panSpeed * dt;
        if (phi < 1)
            phi = 1;
        camera.euler_angle(phi, theta);
    }
        
}
void updateDT()
{
    last = current;
    current = glfwGetTime();
    dt = current - last;
}
int randint(int start, int end)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(start, end);
    return dist(rng);
}
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
