#version 330

precision highp float;

in vec3 position;
in vec3 normal;
in vec2 map1;

out Fragment
{
    vec2 texCoord;
} fragment;

uniform mat4 mvpMatrix;

void main(void)
{
    fragment.texCoord = map1;
    gl_Position = mvpMatrix * vec4(position, 1.0);
}