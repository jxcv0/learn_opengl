#version 330 core

out vec4 frag_colour;

uniform vec4 u_color; // (see vert)

void main() {
    frag_colour = u_color;
}