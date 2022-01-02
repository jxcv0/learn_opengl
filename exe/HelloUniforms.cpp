#include "glad.h"
#include "Shaders.hpp"

#include "Util.hpp"

#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Window
    GLFWwindow *window = glfwCreateWindow(1280, 720, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 1280, 720);
    glfwSetFramebufferSizeCallback(window, util::framebuffer_size_callback);

    // Triangle vertices and colours
    float vertices[] = {
        0.5f, -0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f,
    };

    // Vertex shader
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    shaders::load_shader(vertex_shader, "shaders/HelloUniforms.vert");
    glCompileShader(vertex_shader);

    // Fragment shader
    unsigned int frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    shaders::load_shader(frag_shader, "shaders/HelloUniforms.frag");
    glCompileShader(frag_shader);

    // Check vert shader compile success
    int success;
    char info_log[512];

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
            << info_log << std::endl;
    }

    // Check frag shader compile success
    glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(frag_shader, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
            << info_log << std::endl;
    }

    // Shader program
    unsigned int shader_pgrm = glCreateProgram();
    glAttachShader(shader_pgrm, vertex_shader);
    glAttachShader(shader_pgrm, frag_shader);
    glLinkProgram(shader_pgrm);

    // Check shader link success
    glGetProgramiv(shader_pgrm, GL_LINK_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shader_pgrm, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::VERTEX::LINKING_FAILED\n"
            << info_log << std::endl;
    }

    // Delete shaders
    glDeleteShader(vertex_shader);
    glDeleteShader(frag_shader);

    // VBO and VAO and linking vertex attributes
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbinding for safety
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);   

    // Render loop
    while(!glfwWindowShouldClose(window)) {
        util::process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_pgrm);

        // Update uniform
        float t = glfwGetTime();
        float green_val = (sin(t) / 2.0f) + 0.5f;
        int loc = glad_glGetUniformLocation(shader_pgrm, "u_color");
        glUniform4f(loc, 0, green_val, 0, 0);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Deallocate
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader_pgrm);
    
    glfwTerminate();
    return 0;
}