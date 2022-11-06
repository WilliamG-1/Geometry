#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "shader.h"
#include "vertexArrayObject.h"
#include "renderer.h"
#include "square.h"
#include "camera.h"
#include "transformations.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void updateDT();

float yMovement = 0.0f;
float xMovement = 0.0f;
float dt = 0;
float current = 0;
float last = 0;
float rotateAmount = 0.0f;
float scalar = 1;
bool rotate = false;
bool scale = false;
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

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Shader shader;
    shader.init_shaders("shaders/vertex.vert", "shaders/fragment.frag");
    Renderer renderer;
    OrthographicCamera o_Camera(800.0f, 600.0f);
    o_Camera.moveView(glm::vec3(30.0f, -400.0f, 0.0f));
    
    Square square(50.0f, 50.0f, 200.0f);
    Square square2(500.0f, 200.0f, 100.0f);

    shader.setUniformMat4f("u_ViewProjection", o_Camera.get_projection_view_matrix());

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2, 0.39f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        o_Camera.moveView(glm::vec3(xMovement, yMovement, 0.0f));
        shader.setUniformMat4f("u_ViewProjection", o_Camera.get_projection_view_matrix());

        Transformations::rotate(square.get_model(), square, square.get_side(), rotateAmount);
        shader.setUniformMat4f("u_Model", square.get_model());
        renderer.draw2D(shader, square);

        Transformations::rotate(square2.get_model(), square2, square2.get_side(), rotateAmount);
        shader.setUniformMat4f("u_Model", square2.get_model());
        renderer.draw2D(shader, square2);
        

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
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        xMovement -= 500 * dt;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        xMovement += 500 * dt;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        yMovement += 500 * dt;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        yMovement -= 500 * dt;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        rotateAmount += 90 * dt;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        rotateAmount -= 90 * dt;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        scale = true;
        scalar += dt * 5;
    } else scale = false;
        
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        scale = true;
        scalar -= dt * 5;
    } else scale = false;
        
}
void updateDT()
{
    last = current;
    current = glfwGetTime();
    dt = current - last;
}
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
