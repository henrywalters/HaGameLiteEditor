#version 300 es

precision highp float;

in vec2 TexCoord;
in vec3 FragPos;

out vec4 FragColor;

uniform vec4 Color;

void main() {
    FragColor = Color;
}