#version 330

in vec2 vTexCoord;

uniform sampler2DMS origImage;
uniform sampler2DMS origDepth;

out vec4 oColor;

void main(void) 
{ 
    const int sampleCount = 8;
    vec4 vColor[sampleCount];
	float vDepth[sampleCount];
	int vSurfOrder[sampleCount];
	
	vec2 tmp = floor(textureSize(origDepth) * vTexCoord); 
	for (int i = 0; i < sampleCount; i++)
	{
		vSurfOrder[i] = i;
        vColor[i] = texelFetch(origImage, ivec2(tmp), i);
	    vDepth[i] = texelFetch(origDepth, ivec2(tmp), i).r;
	}
	
	for (int j = 0; j < sampleCount; j++)
    {
		bool bFinished = true;
        for (int i = 0; i < sampleCount - 1; i++)
	    {
	        float temp1 = vDepth[vSurfOrder[i]];
	        float temp2 = vDepth[vSurfOrder[i + 1]];
    	    
	        if (temp2 < temp1)
	        {
	            int tempIndex = vSurfOrder[i];
	            vSurfOrder[i] = vSurfOrder[i + 1];
	            vSurfOrder[i + 1] = tempIndex;
	            bFinished = false;
	        }
	    }
	    
	    if (bFinished)
            j = 8;
	}
	
	bool bFoundFirstColor = false;
	vec4 summedColor = vec4(0.0);
	for (int i = sampleCount - 1; i >= 0; i--)
    {
		int surfIndex = vSurfOrder[i];
		if(vColor[surfIndex].a > 0.001)
		{
			if (bFoundFirstColor == false)
			{
				summedColor = vColor[surfIndex];
				bFoundFirstColor = true;
			}
			else
			{
				summedColor.rgb = summedColor.rgb * (1 - vColor[surfIndex].a) + vColor[surfIndex].rgb * vColor[surfIndex].a;
			}
		}
    }
   
    oColor = summedColor;
   
    int surfIndex = 2;
    float val = vDepth[vSurfOrder[surfIndex]];
    //oColor = vec4(val, val, val, 1.0);
    //oColor = vec4(vColor[vSurfOrder[surfIndex]].rgb, 1.0);
    //oColor = vec4(vColor[0].rgb, 1.0);
    oColor.a = 1.0;
}