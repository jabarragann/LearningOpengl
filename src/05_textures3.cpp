
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <MyGlfwWindow.h>
#include <iostream>
#include <Shader.h>
#include <Texture.h>
#include <filesystem>

// Define the path of the bin folder at compilation
#ifndef BIN_PATH
#define BIN_PATH ./ bin /
#endif

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define BIN_PATH_STR TOSTRING(BIN_PATH)

float vertices[] = {
    // positions      // colors      //texture coords
    0.5f, 0.5f, 0.0f, 0.0, 0.0, 1.0, 1.0f, 1.0f,   // top right
    0.5f, -0.5f, 0.0f, 1.0, 0.0, 0.0, 1.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0, 0.0f, 0.0f, // bottom left
    -0.5f, 0.5f, 0.0f, 0.0, 1.0, 1.0, 0.0f, 1.0f   // top left
};

unsigned int indices[] = {
    // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
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

    std::filesystem::path binary_path = std::filesystem::absolute(BIN_PATH_STR);

    // SHADER CONFIG
    std::string vertex_shader = (binary_path / "../shaders/05_textures3.vs").string();
    std::string fragment_shader = (binary_path / "../shaders/05_textures3.fs").string();
    Shader ourShader(vertex_shader.c_str(), fragment_shader.c_str());

    // TEXTURE CONFIG
    std::string text1_path = (binary_path / "../textures/container.jpg").string();
    Texture my_texture1(text1_path);

    std::string text2_path = (binary_path / "../textures/awesomeface.png").string();
    Texture my_texture2(text2_path);

    // BUFFER CONFIG
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a vertex buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 4. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);                   // Vertex positions
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float))); // Colors
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float))); // Texture coords
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex
    // buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    // UNIFORM LOCATIONS
    int resolution_uniform_location = glGetUniformLocation(ourShader.ID, "u_resolution");
    int time_uniform_location = glGetUniformLocation(ourShader.ID, "u_time");

    ourShader.activate_shader();
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture2"), 1);

    while (!glfwWindowShouldClose(my_window->window_ptr))
    {
        my_window->processInput();
        glViewport(0, 0, my_window->width, my_window->height);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, my_texture1.texture_id);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, my_texture2.texture_id);

        // shader uniforms
        ourShader.activate_shader();
        glUniform2f(resolution_uniform_location, my_window->width, my_window->height);

        // draw objects
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        // glfw swap buffers
        glfwSwapBuffers(my_window->window_ptr);
        glfwPollEvents();
    }

    glfwTerminate();

    std::cout << "Closing app" << std::endl;

    return 0;
}