#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Shader.h>
#include <filesystem>
#include <MyGlfwWindow.h>

float vertices[] = {
    // first triangle
    0.5f, 0.5f, 0.0f,   // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, 0.5f, 0.0f,  // top left
                        // second triangle
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f, 0.5f, 0.0f   // top left
};


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    MyGlfwWindow *my_window = new MyGlfwWindow(800, 600, "LearnOpenGl!");
    my_window->make_context_current();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // SHADER CONFIG
    std::filesystem::path shaderAbsPath = std::filesystem::absolute("./shaders/");

    std::string vertex_shader = (shaderAbsPath / "shader1.vs").string();
    std::string fragment_shader = (shaderAbsPath / "shader1.fs").string();

    Shader ourShader(vertex_shader.c_str(), fragment_shader.c_str());

    // BUFFER CONFIG
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex
    // buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // RENDER LOOP
    while (!glfwWindowShouldClose(my_window->window_ptr))
    {
        my_window->processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw first half
        glViewport(0, 0, my_window->width / 2, my_window->height);
        ourShader.activate_shader();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Draw second half
        glViewport(my_window->width / 2, 0, my_window->width / 2, my_window->height);
        ourShader.activate_shader();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // glfw swap buffers
        glfwSwapBuffers(my_window->window_ptr);
        glfwPollEvents();
    }

    glfwTerminate();

    std::cout << "Closing app" << std::endl;

    return 0;
}