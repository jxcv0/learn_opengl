#include "Shaders.hpp"

#include <string>
#include <fstream>
#include <iostream>

/**
 * @brief Read a shader file
 * 
 * @param path the file path
 * @return the shader program as a string
 */
std::string shaders::read_shader_file(const char* path) {
    std::ifstream f_stream(path);

    if (!f_stream.is_open()) {
        std::cerr << "File not found at " << path << "." << std::endl;
        return "";
    }

    std::string str(
        (std::istreambuf_iterator<char>(f_stream)),
        (std::istreambuf_iterator<char>())
    );
    // buffer << f_stream.rdbuf();

    f_stream.close();
    return str;
}

void shaders::shader_source(GLuint shader, const std::string& shader_string) {
    const GLchar *shader_source = shader_string.c_str();
    const GLint shader_length = shader_string.length();

    glShaderSource(shader, 1, &shader_source, &shader_length);
}

void shaders::load_shader(GLuint shader_obj, const char *path) {
    shader_source(shader_obj, read_shader_file(path));
}