#include <gtest/gtest.h>

#include "Shaders.hpp"

TEST(ShadersTests, read_shader_file_test) {
    const char *p_expected = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "\n"
    "void main() {\n"
    "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}";

    std::string expected(p_expected);

    std::string actual = shaders::read_shader_file("shaders/BasicVertexShader.vert");

    ASSERT_EQ(actual, expected);
}