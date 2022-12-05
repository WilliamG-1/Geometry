#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
struct DeltaTime
{
    float last;
    float current;
    float dt;
};

class Window
{
public:
    Window(const char* title, int width, int height)
    {
        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (window == nullptr)
        {
            std::cout << "Error, could not create a window!" << std::endl;
            glfwTerminate();

        }
        
        glfwMakeContextCurrent(window);
        // Set FramBuffer Callback (to resize window and viewport)
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
        });

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }
    }
    GLFWwindow* getWindow() { return window; }

private:
    GLFWwindow* window;
};