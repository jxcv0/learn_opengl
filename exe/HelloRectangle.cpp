#include "Shaders.hpp"
#include "Util.hpp"
#include "glad.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <string.h>

int main(int argc, char const *argv[]) {

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

    // Rectangle
    float vertices[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f,  -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    unsigned int indecies[] = {
        0, 1, 3,
        1, 2, 3        
    };

    // Vertex shader
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    shaders::load_shader(vertex_shader, "shaders/BasicVertexShader.vert");
    glCompileShader(vertex_shader);

    // Fragment shader
    unsigned int frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    shaders::load_shader(frag_shader, "shaders/OrangeFragmentShader.frag");
    glCompileShader(frag_shader);

    // Check shader compile success
    int success;
    char info_log[512];

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
            << info_log << std::endl;
    }

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

    // EBO, VBO, VAO and linking vertex attributes
    unsigned int EBO, VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), indecies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbinding for safety?
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    if (argc != 2) {
        std::cerr << 
            "Usage:\n" <<
            "   hellorectangle <arg>\n" <<
            "       -l - wireframe mode\n" <<
            "       -f - fill mode\n" << 
        std::endl;
        
        return EXIT_FAILURE;
    }
    

    if (strcmp(argv[1], "-l") == 0) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else if (strcmp(argv[1], "-f") == 0) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } else {
        std::cerr << 
            "Usage:\n" <<
            "   hellorectangle <arg>\n" <<
            "       -l - wireframe mode\n" <<
            "       -f - fill mode\n" << 
        std::endl;

        return EXIT_FAILURE;
    }

    // Render loop
    while(!glfwWindowShouldClose(window)) {
        util::process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_pgrm);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0); // why?

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