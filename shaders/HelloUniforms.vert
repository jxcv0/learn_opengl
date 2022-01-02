#version 330 core

layout (location = 0) in vec3 aPos; // pos

void main() {
    gl_Position = vec4(aPos, 1.0); // swizzle my shizzle yo
}