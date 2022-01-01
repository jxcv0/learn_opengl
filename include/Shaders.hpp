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

    void shader_source(GLuint shader, const std::string& shader_string);

    void load_shader(GLuint shader_obj, const char *path);
} // namespace shaders

#endif