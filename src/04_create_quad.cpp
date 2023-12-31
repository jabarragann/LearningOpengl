#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Shader.h>
#include <filesystem>
#include <string>

// Define the path of the bin folder at compilation
#ifndef BIN_PATH
    #define BIN_PATH ./bin/
#endif
// Magic to surround a macro with quotes
// Taken from: https://stackoverflow.com/questions/49810726/how-can-i-pass-a-string-as-a-preprocessor-token
// Also see the end of: https://gcc.gnu.org/onlinedocs/cpp/Stringizing.html#:~:text=When%20a%20macro%20parameter%20is,This%20is%20called%20stringizing
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define BIN_PATH_STR TOSTRING(BIN_PATH)

float vertices[] = {
     1.0f,  1.0f, 0.0f,  // top right
     1.0f, -1.0f, 0.0f,  // bottom right
    -1.0f, -1.0f, 0.0f,  // bottom left
    -1.0f,  1.0f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};  

void framebuffer_size_callback(GLFWwindow* , int width, int height)
{
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int width = 400;
    int height = 400;
    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    } 

    // SHADER CONFIG
    std::filesystem::path binary_path = std::filesystem::absolute(BIN_PATH_STR);

    std::string vertex_shader = (binary_path / "../shaders/shader3.vs").string();
    std::string fragment_shader =  (binary_path / "../shaders/shader4.fs").string();
    
    Shader ourShader(vertex_shader.c_str(), fragment_shader.c_str());

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex 
    // buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 

    // Uniform locations
    int resolution_uniform_location = glGetUniformLocation(ourShader.ID, "u_resolution");
    int time_uniform_location = glGetUniformLocation(ourShader.ID, "u_time");

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // RENDER LOOP
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw
        ourShader.activate_shader();
        // Update u_resolution
        glfwGetWindowSize(window, &width, &height);
        glUniform2f(resolution_uniform_location, width, height);
        // Update u_time
        float time_value = glfwGetTime();
        glUniform1f(time_uniform_location, time_value);
         
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);
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