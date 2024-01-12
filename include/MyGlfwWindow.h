#pragma once

#include <GLFW/glfw3.h>
#include <string>

class MyGlfwWindow
{
public:
    int width;
    int height;
    std::string title;
    GLFWwindow *window_ptr;

    MyGlfwWindow(int width, int height, std::string);
    void resize_window(GLFWwindow *window, int width, int height);

    void make_context_current() { glfwMakeContextCurrent(window_ptr); };

    void processInput();
};