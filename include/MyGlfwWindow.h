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

    void configure_callbacks();
    void resize_window_cb(GLFWwindow *window, int width, int height);
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    void make_context_current() { glfwMakeContextCurrent(window_ptr); };

    void processInput();
};