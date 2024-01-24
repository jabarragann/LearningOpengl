#include <iostream>
#include <MyGlfwWindow.h>
#include <stdexcept>

MyGlfwWindow::MyGlfwWindow(int width, int height, std::string title) : width(width), height(height), title(title)
{

    window_ptr = glfwCreateWindow(this->width, this->height, title.c_str(), NULL, NULL);
    glfwSetWindowUserPointer(window_ptr, this);

    if (window_ptr == NULL)
    {
        glfwTerminate();
        std::runtime_error("Failed to create GLFW window");
    }

    configure_callbacks();
}
void MyGlfwWindow::configure_callbacks()
{
    // Configure callbacks
    // The lambda function can only get access to the class method by using `glfwGetWindowUserPointer`
    void (*lambda_resize_window)(GLFWwindow *, int, int) = [](GLFWwindow *w, int width, int height)
    {
        static_cast<MyGlfwWindow *>(glfwGetWindowUserPointer(w))->resize_window_cb(w, width, height);
    };
    glfwSetFramebufferSizeCallback(window_ptr, lambda_resize_window);

    auto lambda_key_callback = [](GLFWwindow *w, int key, int scancode, int action, int mods)
    {
        static_cast<MyGlfwWindow *>(glfwGetWindowUserPointer(w))->key_callback(w, key, scancode, action, mods);
    };
    glfwSetKeyCallback(window_ptr, lambda_key_callback);
}

void MyGlfwWindow::resize_window_cb(GLFWwindow *window, int width, int height)
{
    // MyGlfwWindow *my_window_ptr = static_cast<MyGlfwWindow *>(glfwGetWindowUserPointer(window));
    // my_window_ptr->width = width;
    // my_window_ptr->height = height;
    // std::cout << "Window resized to " << width << "x" << height << std::endl;

    this->width = width;
    this->height = height;
}

void MyGlfwWindow::processInput()
{
    if (glfwGetKey(window_ptr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window_ptr, true);
}

void MyGlfwWindow::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
        std::cout << "E key pressed" << std::endl;
    else if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window_ptr, true);
    else
        std::cout << "Key pressed: " << key << std::endl;
}
