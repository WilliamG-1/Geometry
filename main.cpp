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
void processInput(GLFWwindow *window);
int randint(int first, int second);
void updateDT();

float yMovement = 0.0f;
float xMovement = 0.0f;
float zMovement = 9.0f;
float dt = 0;
float current = 0;
float last = 0;
float rotateAmount = 0.0f;
float xRotation = 0;
float yRotation = 0;
float zRotation = 0;
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

    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Shader shader;
    shader.init_shaders("shaders/vertex.vert", "shaders/fragment.frag");
    Renderer renderer;
    //OrthographicCamera o_Camera(800.0f, 600.0f);
    PerspectiveCamera p_Camera(45.0f, 800, 600, 0.1f, 90.0f);
    p_Camera.moveView(glm::vec3(0.0f, 0.0f, -5.0f));
    //o_Camera.moveView(glm::vec3(30.0f, -400.0f, 0.0f));
    
    Square square(50.0f, 50.0f, 200.0f, true);
    Square square2(500.0f, 200.0f, 100.0f, true, -5);
    Cube cube(1.0f);

    std::vector<Cube> v_Cubes;
    for (int i = 1; i < 90; i++)
    {
        v_Cubes.push_back(Cube(1.0f));
        Transformations::translate3D(v_Cubes[i - 1].get_model_matrix(), randint(-10, 10), randint(-10, 10), randint(-10, 10));
        Transformations::rotate3D(v_Cubes[i - 1].get_model_matrix(), i * 10, i * 33, i % 3, glm::vec3(1.0f, 1.0f, 1.0f));
    }
    //Cube cube2(3.0f);
    //shader.setUniformMat4f("u_ViewProjection", o_Camera.get_projection_view_matrix());
    shader.setUniformMat4f("u_ViewProjection", p_Camera.get_projection_view_matrix());
    shader.setUniformMat4f("u_Model", cube.get_model_matrix());
    glEnable(GL_DEPTH_TEST);
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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Transformations::rotate3D(cube.get_model_matrix(), xRotation, yRotation, 0, glm::vec3(1.0f, 1.0f, 1.0f)); // This is temrprary lol
        //shader.setUniformMat4f("u_Model", cube.get_model_matrix());
        renderer.draw3D(shader, cube);
        for (Cube& cube : v_Cubes)
            renderer.draw3D(shader, cube);
        //Transformations::rotate3D(cube2.get_model_matrix(), square2, 3, xRotation, glm::vec3(0, 1.0f, 0.0f) ); // This is temrprary lol
        //shader.setUniformMat4f("u_Model", cube2.get_model_matrix());
        //renderer.draw3D(shader, cube2);

        p_Camera.moveView(glm::vec3(xMovement, yMovement, zMovement));
        shader.setUniformMat4f("u_ViewProjection", p_Camera.get_projection_view_matrix());

        // Transformations::rotate3D(square.get_model(), square, square.get_side(), xRotation, glm::vec3(1, 0.0f, 0.0f));
        // shader.setUniformMat4f("u_Model", square.get_model());
        // renderer.draw2D(shader, square);

        // //Transformations::rotate2D(square2.get_model(), square2, square2.get_side(), rotateAmount);
        // shader.setUniformMat4f("u_Model", square2.get_model());
        // renderer.draw2D(shader, square2);
        
        xRotation = 0;
        yRotation = 0;
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
    // Camera movement 
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        xMovement -= 5 * dt;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        xMovement += 5 * dt;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        zMovement -= 5 * dt;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        zMovement += 5 * dt;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        yMovement += 5 * dt;   
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        yMovement -= 5 * dt;   


    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        yRotation = -90.5 * dt;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        yRotation = 90.5 * dt;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        xRotation = -90.5 * dt;     
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        xRotation = 90.5 * dt;
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
