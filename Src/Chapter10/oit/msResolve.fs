#version 330

in vec2 vTexCoord;

uniform sampler2DMS origImage;
uniform int sampleCount;

out vec4 oColor;

void main(void) 
{ 
	vec2 tmp = floor(textureSize(origImage) * vTexCoord); 

	vec4 vColor = vec4(0.0);
	
	for (int i = 0; i < sampleCount; i++)
	{
	    vColor += texelFetch(origImage, ivec2(tmp), i);
	}

    oColor = vColor / sampleCount;
    oColor.a = 1.0f;
}