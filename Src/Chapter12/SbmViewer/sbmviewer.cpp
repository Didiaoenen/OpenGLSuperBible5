#include "sbmviewer.h"
#include "sbm.h"

bool LoadBMPTexture(const char* szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode)
{
	GLbyte* pBits;
	GLint iWidth, iHeight;

	pBits = gltReadBMPBits(szFileName, &iWidth, &iHeight);
	if (pBits == NULL)
		return false;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

	if (minFilter == GL_LINEAR_MIPMAP_LINEAR || minFilter == GL_LINEAR_MIPMAP_NEAREST || minFilter == GL_NEAREST_MIPMAP_LINEAR || minFilter == GL_NEAREST_MIPMAP_NEAREST)
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iWidth, iHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, pBits);

	free(pBits);

	return true;
}

SBMViewer::SBMViewer(void)
    : screenWidth(1024)
    , screenHeight(768)
{

}

void SBMViewer::Initialize(void)
{
    unsigned int e;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

	glGenTextures(1, textures);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
    LoadBMPTexture("../../Models/Ninja/NinjaComp.bmp", GL_LINEAR, GL_LINEAR, GL_CLAMP);

    instancingProg = gltLoadShaderPair("sbmviewer.vs", "sbmviewer.fs");

    object = new SBObject;
    object->LoadFromSBM("../../Models/Ninja/ninja.sbm", 0, 1, 2);

    unsigned int i;

    for (i = 0; i < object->GetAttributeCount(); i++) {
        glBindAttribLocation(instancingProg, i, object->GetAttributeName(i));
        e = glGetError();
    }

    glLinkProgram(instancingProg);
}

void SBMViewer::Shutdown(void)
{
    delete object;
}

void SBMViewer::Resize(GLsizei nWidth, GLsizei nHeight)
{
	screenWidth = nWidth;
	screenHeight = nHeight;
	glViewport(0, 0, nWidth, nHeight);

	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);

	viewFrustum.SetPerspective(35.0f, float(nWidth) / float(nHeight), 1.0f, 100.0f);
	projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
}

void SBMViewer::Render(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	M3DMatrix44f mCamera;
	cameraFrame.GetCameraMatrix(mCamera);

	modelViewMatrix.PushMatrix();
	modelViewMatrix.Translate(0.0f, 0.2f, -2.5f);

	modelViewMatrix.PushMatrix();
	modelViewMatrix.MultMatrix(mCamera);
	modelViewMatrix.Translate(0.0f, -0.6f, 0.0);
	modelViewMatrix.Scale(0.02f, 0.006f, 0.02f);

	glUseProgram(instancingProg);
	glUniformMatrix4fv(glGetUniformLocation(instancingProg, "mvpMatrix"), 1, GL_FALSE, transformPipeline.GetModelViewProjectionMatrix());
	glUniform1i(glGetUniformLocation(instancingProg, "vColorMap"), 0);

	object->Render(0);

	modelViewMatrix.PopMatrix();
	modelViewMatrix.PopMatrix();

	unsigned int e = glGetError();
}