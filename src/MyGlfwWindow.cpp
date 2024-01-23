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

    // Configure callbacks
    // The lambda function can only get access to the class method by using `glfwGetWindowUserPointer`
    void (*lambda_resize_window)(GLFWwindow *, int, int) = [](GLFWwindow *w, int width, int height)
    {
        static_cast<MyGlfwWindow *>(glfwGetWindowUserPointer(w))->resize_window(w, width, height);
    };
    glfwSetFramebufferSizeCallback(window_ptr, lambda_resize_window);
}

void MyGlfwWindow::resize_window(GLFWwindow *window, int width, int height)
{
    // MyGlfwWindow *my_window_ptr = static_cast<MyGlfwWindow *>(glfwGetWindowUserPointer(window));
    // my_window_ptr->width = width;
    // my_window_ptr->height = height;

    this->width = width;
    this->height = height;
}

void MyGlfwWindow::processInput()
{
    if (glfwGetKey(window_ptr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window_ptr, true);
}