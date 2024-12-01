#version 330

in vec3 vVertex;
in vec3 vNormal;
in vec2 vTexCoord0;

uniform mat4 mvMatrix;
uniform mat4 pMatrix;

out vec2 vTexCoord;

void main()
{
	vTexCoord = vTexCoord0;

	mat4 mvpMatrix = pMatrix * mvMatrix;
	gl_Position = mvpMatrix * vec4(vVertex, 1.0); 
}