#version 330 core

layout (location = 0) in vec3 aPos; // pos
layout (location = 1) in vec3 aCol; // col

out vec3 col;

void main() {
    gl_Position = vec4(aPos, 1.0); // swizzle my shizzle yo
    col = aCol;
}