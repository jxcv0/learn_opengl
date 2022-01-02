#version 330 core

out vec4 frag_colour;

in vec3 col; // see vert

void main() {
    frag_colour = vec4(col, 1.0);
}