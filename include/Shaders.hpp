#ifndef SHADERS_HPP
#define SHADERS_HPP

#include "glad.h"

#include <string>

namespace shaders {

    /**
     * @brief Read a shader file
     * 
     * @param path the file path
     * @return the shader program as a string
     */
    std::string read_shader_file(const char* path);

    /**
     * @brief Assign shader source code
     * 
     * @param shader the shader onj int
     * @param shader_string the shader code
     */
    void shader_source(GLuint shader, const std::string& shader_string);

    /**
     * @brief Attach vertex shader source code to a shader object and compile
     * 
     * @param shader_obj the shader obj
     * @param path the path to the shader source code
     */
    void load_shader(GLuint shader_obj, const char *path);
} // namespace shaders

#endif