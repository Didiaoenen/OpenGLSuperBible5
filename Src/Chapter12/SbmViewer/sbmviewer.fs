#version 330

precision highp float;

uniform vec4 vColor;
uniform sampler2D vColorMap;

in Fragment
{
    vec2 texCoord;
} fragment;

out vec4 color;

void main(void)
{
    color = texture(vColorMap, fragment.texCoord);
}