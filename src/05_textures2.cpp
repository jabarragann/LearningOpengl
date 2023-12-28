#include <glad/glad.h>
#include <GLFW/glfw3.h>
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

void framebuffer_size_callback(GLFWwindow *, int width, int height)
{
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

GLFWwindow *create_window(int width, int height, const char *title)
{

    GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (window == NULL)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    return window;
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int width = 400;
    int height = 400;
    GLFWwindow *window = create_window(width, height, "LearnOpenGL");

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    std::filesystem::path binary_path = std::filesystem::absolute(BIN_PATH_STR);

    // SHADER CONFIG
    std::string vertex_shader = (binary_path / "../shaders/shader5.vs").string();
    std::string fragment_shader = (binary_path / "../shaders/shader5.fs").string();
    Shader ourShader(vertex_shader.c_str(), fragment_shader.c_str());

    // TEXTURE CONFIG
    int tex_width, tex_height, nrChannels;
    std::string text1_path = (binary_path / "../textures/container.jpg").string();
    Texture my_texture(text1_path);

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

    while (!glfwWindowShouldClose(window))
    {
        process_input(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // shader uniforms
        ourShader.activate_shader();
        glfwGetWindowSize(window, &width, &height);
        glUniform2f(resolution_uniform_location, width, height);

        // draw objects
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        // glfw swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    std::cout << "Closing app" << std::endl;

    return 0;
}