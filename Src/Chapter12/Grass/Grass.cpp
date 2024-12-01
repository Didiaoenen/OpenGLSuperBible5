// grassShader.cpp
// OpenGL SuperBible
// Demonstrates the effect of the 'noperspective' interpolation qualifier
// Program by Graham Sellers

#include <GLTools.h>    // OpenGL toolkit
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
#include <GLGeometryTransform.h>
#include "StopWatch.h"

#include <math.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#include <GL/freeglut_ext.h>
#ifdef linux
#include <cstdlib> 
#endif


GLFrame             viewFrame;
GLFrustum           viewFrustum;
GLMatrixStack       modelViewMatrix;
GLMatrixStack       projectionMatrix;
GLGeometryTransform transformPipeline;

GLuint  grassShader;      // The perspective demonstration shader
GLint   locMVP;                 // The location of the ModelViewProjection matrix uniform

GLuint  length_texture;         //
GLuint  orientation_texture;
GLuint  grasspalette_texture;
GLuint  grasscolor_texture;
GLuint  bend_texture;

GLuint  vao;                    // The VAO
GLuint  vertexBuffer;           // Geometry VBO

const unsigned char grasspalette_data[]  =
{
    0x5E, 0x5F, 0x15, 0x5E, 0x5F, 0x14, 0x5E, 0x5F,
    0x14, 0x5E, 0x5F, 0x14, 0x5E, 0x5F, 0x14, 0x5E,
    0x5F, 0x14, 0x5E, 0x5F, 0x14, 0x5E, 0x5F, 0x14,
    0x5F, 0x5F, 0x14, 0x5F, 0x60, 0x14, 0x5F, 0x60,
    0x14, 0x5F, 0x60, 0x14, 0x5F, 0x60, 0x14, 0x5F,
    0x60, 0x13, 0x5F, 0x60, 0x13, 0x5F, 0x60, 0x13,
    0x60, 0x60, 0x13, 0x60, 0x61, 0x13, 0x60, 0x61,
    0x13, 0x60, 0x61, 0x13, 0x60, 0x61, 0x13, 0x60,
    0x61, 0x13, 0x60, 0x61, 0x13, 0x60, 0x61, 0x13,
    0x61, 0x61, 0x13, 0x61, 0x62, 0x12, 0x61, 0x62,
    0x12, 0x61, 0x62, 0x12, 0x61, 0x62, 0x12, 0x61,
    0x62, 0x12, 0x61, 0x62, 0x12, 0x62, 0x62, 0x12,
    0x62, 0x62, 0x12, 0x62, 0x63, 0x12, 0x62, 0x63,
    0x12, 0x62, 0x63, 0x12, 0x62, 0x63, 0x12, 0x62,
    0x63, 0x11, 0x62, 0x63, 0x11, 0x63, 0x63, 0x11,
    0x63, 0x63, 0x11, 0x63, 0x64, 0x11, 0x63, 0x64,
    0x11, 0x63, 0x64, 0x11, 0x63, 0x64, 0x11, 0x63,
    0x64, 0x11, 0x63, 0x64, 0x11, 0x64, 0x64, 0x11,
    0x64, 0x64, 0x11, 0x64, 0x64, 0x10, 0x64, 0x65,
    0x10, 0x64, 0x65, 0x10, 0x64, 0x65, 0x10, 0x64,
    0x65, 0x10, 0x65, 0x65, 0x10, 0x65, 0x65, 0x10,
    0x65, 0x65, 0x10, 0x65, 0x65, 0x10, 0x65, 0x66,
    0x10, 0x65, 0x66, 0x10, 0x65, 0x66, 0x10, 0x65,
    0x66, 0x0F, 0x66, 0x66, 0x0F, 0x66, 0x66, 0x0F,
    0x66, 0x66, 0x0F, 0x66, 0x66, 0x0F, 0x66, 0x67,
    0x0F, 0x66, 0x67, 0x0F, 0x66, 0x67, 0x0F, 0x66,
    0x67, 0x0F, 0x67, 0x67, 0x0F, 0x67, 0x67, 0x0F,
    0x67, 0x67, 0x0F, 0x67, 0x67, 0x0E, 0x67, 0x68,
    0x0E, 0x67, 0x68, 0x0E, 0x67, 0x68, 0x0E, 0x67,
    0x68, 0x0E, 0x68, 0x68, 0x0E, 0x68, 0x68, 0x0E,
    0x68, 0x68, 0x0E, 0x68, 0x68, 0x0E, 0x68, 0x69,
    0x0E, 0x68, 0x69, 0x0E, 0x68, 0x69, 0x0E, 0x69,
    0x69, 0x0D, 0x69, 0x69, 0x0D, 0x69, 0x69, 0x0D,
    0x69, 0x69, 0x0D, 0x69, 0x69, 0x0D, 0x69, 0x69,
    0x0D, 0x69, 0x6A, 0x0D, 0x69, 0x6A, 0x0D, 0x6A,
    0x6A, 0x0D, 0x6A, 0x6A, 0x0D, 0x6A, 0x6A, 0x0D,
    0x6A, 0x6A, 0x0D, 0x6A, 0x6A, 0x0C, 0x6A, 0x6A,
    0x0C, 0x6A, 0x6B, 0x0C, 0x6A, 0x6B, 0x0C, 0x6B,
    0x6B, 0x0C, 0x6B, 0x6B, 0x0C, 0x6B, 0x6B, 0x0C,
    0x6B, 0x6B, 0x0C, 0x6B, 0x6B, 0x0C, 0x6B, 0x6B,
    0x0C, 0x6B, 0x6C, 0x0C, 0x6C, 0x6C, 0x0C, 0x6C,
    0x6C, 0x0B, 0x6C, 0x6C, 0x0B, 0x6C, 0x6C, 0x0B,
    0x6C, 0x6C, 0x0B, 0x6C, 0x6C, 0x0B, 0x6C, 0x6C,
    0x0B, 0x6C, 0x6D, 0x0B, 0x6D, 0x6D, 0x0B, 0x6D,
    0x6D, 0x0B, 0x6D, 0x6D, 0x0B, 0x6D, 0x6D, 0x0B,
    0x6D, 0x6D, 0x0B, 0x6D, 0x6D, 0x0A, 0x6D, 0x6D,
    0x0A, 0x6D, 0x6E, 0x0A, 0x6E, 0x6E, 0x0A, 0x6E,
    0x6E, 0x0A, 0x6E, 0x6E, 0x0A, 0x6E, 0x6E, 0x0A,
    0x6E, 0x6E, 0x0A, 0x6E, 0x6E, 0x0A, 0x6E, 0x6E,
    0x0A, 0x6F, 0x6F, 0x0A, 0x6F, 0x6F, 0x0A, 0x6F,
    0x6F, 0x0A, 0x6F, 0x6F, 0x09, 0x6F, 0x6F, 0x09,
    0x6F, 0x6F, 0x09, 0x6F, 0x6F, 0x09, 0x6F, 0x6F,
    0x09, 0x6F, 0x6F, 0x09, 0x6F, 0x6F, 0x09, 0x70,
    0x70, 0x09, 0x70, 0x70, 0x09, 0x70, 0x70, 0x09,
    0x70, 0x70, 0x09, 0x70, 0x70, 0x09, 0x70, 0x70,
    0x09, 0x70, 0x70, 0x09, 0x70, 0x70, 0x08, 0x71,
    0x71, 0x08, 0x71, 0x71, 0x08, 0x71, 0x71, 0x08,
    0x71, 0x71, 0x08, 0x71, 0x71, 0x08, 0x71, 0x71,
    0x08, 0x71, 0x71, 0x08, 0x71, 0x71, 0x08, 0x71,
    0x71, 0x08, 0x72, 0x72, 0x08, 0x72, 0x72, 0x08,
    0x72, 0x72, 0x08, 0x72, 0x72, 0x08, 0x72, 0x72,
    0x07, 0x72, 0x72, 0x07, 0x72, 0x72, 0x07, 0x72,
    0x72, 0x07, 0x73, 0x73, 0x07, 0x73, 0x73, 0x07,
    0x73, 0x73, 0x07, 0x73, 0x73, 0x07, 0x73, 0x73,
    0x07, 0x73, 0x73, 0x07, 0x73, 0x73, 0x07, 0x73,
    0x73, 0x07, 0x74, 0x74, 0x07, 0x74, 0x74, 0x07,
    0x74, 0x74, 0x07, 0x74, 0x74, 0x06, 0x74, 0x74,
    0x06, 0x74, 0x74, 0x06, 0x74, 0x74, 0x06, 0x74,
    0x74, 0x06, 0x74, 0x74, 0x06, 0x75, 0x75, 0x06,
    0x75, 0x75, 0x06, 0x75, 0x75, 0x06, 0x75, 0x75,
    0x06, 0x75, 0x75, 0x06, 0x75, 0x75, 0x06, 0x75,
    0x75, 0x06, 0x75, 0x75, 0x06, 0x76, 0x76, 0x05,
    0x76, 0x76, 0x05, 0x76, 0x76, 0x05, 0x76, 0x76,
    0x05, 0x76, 0x76, 0x05, 0x76, 0x76, 0x05, 0x76,
    0x76, 0x05, 0x76, 0x76, 0x05, 0x77, 0x77, 0x05,
    0x77, 0x77, 0x05, 0x77, 0x77, 0x05, 0x77, 0x77,
    0x05, 0x77, 0x77, 0x05, 0x77, 0x77, 0x05, 0x77,
    0x77, 0x04, 0x77, 0x77, 0x04, 0x77, 0x77, 0x04,
    0x78, 0x78, 0x04, 0x78, 0x78, 0x04, 0x78, 0x78,
    0x04, 0x78, 0x78, 0x04, 0x78, 0x78, 0x04, 0x78,
    0x78, 0x04, 0x78, 0x78, 0x04, 0x78, 0x78, 0x04,
    0x79, 0x79, 0x04, 0x79, 0x79, 0x04, 0x79, 0x79,
    0x04, 0x79, 0x79, 0x04, 0x79, 0x79, 0x03, 0x79,
    0x79, 0x03, 0x79, 0x79, 0x03, 0x79, 0x79, 0x03,
    0x79, 0x79, 0x03, 0x7A, 0x7A, 0x03, 0x7A, 0x7A,
    0x03, 0x7A, 0x7A, 0x03, 0x7A, 0x7A, 0x03, 0x7A,
    0x7A, 0x03, 0x7A, 0x7A, 0x03, 0x7A, 0x7A, 0x03,
    0x7A, 0x7A, 0x03, 0x7B, 0x7B, 0x03, 0x7B, 0x7B,
    0x02, 0x7B, 0x7B, 0x02, 0x7B, 0x7B, 0x02, 0x7B,
    0x7B, 0x02, 0x7B, 0x7B, 0x02, 0x7B, 0x7B, 0x02,
    0x7B, 0x7B, 0x02, 0x7C, 0x7C, 0x02, 0x7C, 0x7C,
    0x02, 0x7C, 0x7C, 0x02, 0x7C, 0x7C, 0x02, 0x7C,
    0x7C, 0x02, 0x7C, 0x7C, 0x02, 0x7C, 0x7C, 0x02,
    0x7C, 0x7C, 0x01, 0x7C, 0x7C, 0x01, 0x7D, 0x7D,
    0x01, 0x7D, 0x7D, 0x01, 0x7D, 0x7D, 0x01, 0x7D,
    0x7D, 0x01, 0x7D, 0x7D, 0x01, 0x7D, 0x7D, 0x01,
    0x7D, 0x7D, 0x01, 0x7D, 0x7D, 0x01, 0x7E, 0x7E,
    0x01, 0x7E, 0x7E, 0x01, 0x7E, 0x7E, 0x01, 0x7E,
    0x7E, 0x01, 0x7E, 0x7E, 0x01, 0x7E, 0x7E, 0x00,
    0x7E, 0x7E, 0x00, 0x7E, 0x7E, 0x00, 0x7F, 0x7F,
    0x00, 0x7F, 0x7F, 0x00, 0x7F, 0x7F, 0x00, 0x7F,
    0x7F, 0x00, 0x7F, 0x7F, 0x00, 0x7F, 0x7F, 0x00,
    0x7F, 0x7F, 0x00, 0x7F, 0x7F, 0x00, 0x7F, 0x7F,
    0x00, 0x80, 0x80, 0x00, 0x7F, 0x80, 0x00, 0x7F,
    0x80, 0x00, 0x7F, 0x80, 0x00, 0x7E, 0x80, 0x00,
    0x7E, 0x80, 0x00, 0x7E, 0x80, 0x00, 0x7D, 0x80,
    0x00, 0x7D, 0x80, 0x00, 0x7D, 0x80, 0x00, 0x7C,
    0x80, 0x00, 0x7C, 0x80, 0x00, 0x7C, 0x80, 0x00,
    0x7B, 0x80, 0x00, 0x7B, 0x80, 0x00, 0x7B, 0x80,
    0x00, 0x7A, 0x80, 0x00, 0x7A, 0x80, 0x00, 0x7A,
    0x80, 0x00, 0x79, 0x80, 0x00, 0x79, 0x80, 0x00,
    0x79, 0x80, 0x00, 0x78, 0x80, 0x00, 0x78, 0x80,
    0x00, 0x78, 0x80, 0x00, 0x77, 0x80, 0x00, 0x77,
    0x80, 0x00, 0x77, 0x80, 0x00, 0x76, 0x80, 0x00,
    0x76, 0x80, 0x00, 0x76, 0x80, 0x00, 0x75, 0x80,
    0x00, 0x75, 0x80, 0x00, 0x75, 0x80, 0x00, 0x74,
    0x80, 0x00, 0x74, 0x80, 0x00, 0x74, 0x80, 0x00,
    0x74, 0x80, 0x00, 0x73, 0x80, 0x00, 0x73, 0x80,
    0x00, 0x73, 0x80, 0x00, 0x72, 0x80, 0x00, 0x72,
    0x80, 0x00, 0x72, 0x80, 0x00, 0x71, 0x80, 0x00,
    0x71, 0x80, 0x00, 0x71, 0x80, 0x00, 0x70, 0x80,
    0x00, 0x70, 0x80, 0x00, 0x70, 0x80, 0x00, 0x6F,
    0x80, 0x00, 0x6F, 0x80, 0x00, 0x6F, 0x80, 0x00,
    0x6E, 0x80, 0x00, 0x6E, 0x80, 0x00, 0x6E, 0x80,
    0x00, 0x6D, 0x80, 0x00, 0x6D, 0x80, 0x00, 0x6D,
    0x80, 0x00, 0x6C, 0x80, 0x00, 0x6C, 0x80, 0x00,
    0x6C, 0x80, 0x00, 0x6B, 0x80, 0x00, 0x6B, 0x80,
    0x00, 0x6B, 0x80, 0x00, 0x6A, 0x80, 0x00, 0x6A,
    0x80, 0x00, 0x6A, 0x80, 0x00, 0x69, 0x80, 0x00,
    0x69, 0x80, 0x00, 0x69, 0x80, 0x00, 0x68, 0x80,
    0x00, 0x68, 0x80, 0x00, 0x68, 0x80, 0x00, 0x67,
    0x80, 0x00, 0x67, 0x80, 0x00, 0x67, 0x80, 0x00,
    0x66, 0x80, 0x00, 0x66, 0x80, 0x00, 0x66, 0x80,
    0x00, 0x65, 0x80, 0x00, 0x65, 0x80, 0x00, 0x65,
    0x80, 0x00, 0x64, 0x80, 0x00, 0x64, 0x80, 0x00,
    0x64, 0x80, 0x00, 0x63, 0x80, 0x00, 0x63, 0x80,
    0x00, 0x63, 0x80, 0x00, 0x62, 0x80, 0x00, 0x62,
    0x80, 0x00, 0x62, 0x80, 0x00, 0x62, 0x80, 0x00,
    0x61, 0x80, 0x00, 0x61, 0x80, 0x00, 0x61, 0x80,
    0x00, 0x60, 0x80, 0x00, 0x60, 0x80, 0x00, 0x60,
    0x80, 0x00, 0x5F, 0x80, 0x00, 0x5F, 0x80, 0x00,
    0x5F, 0x80, 0x00, 0x5E, 0x80, 0x00, 0x5E, 0x80,
    0x00, 0x5E, 0x80, 0x00, 0x5D, 0x80, 0x00, 0x5D,
    0x80, 0x00, 0x5D, 0x80, 0x00, 0x5C, 0x80, 0x00,
    0x5C, 0x80, 0x00, 0x5C, 0x80, 0x00, 0x5B, 0x80,
    0x00, 0x5B, 0x80, 0x00, 0x5B, 0x80, 0x00, 0x5A,
    0x80, 0x00, 0x5A, 0x80, 0x00, 0x5A, 0x80, 0x00,
    0x59, 0x80, 0x00, 0x59, 0x80, 0x00, 0x59, 0x80,
    0x00, 0x58, 0x80, 0x00, 0x58, 0x80, 0x00, 0x58,
    0x80, 0x00, 0x57, 0x80, 0x00, 0x57, 0x80, 0x00,
    0x57, 0x80, 0x00, 0x56, 0x80, 0x00, 0x56, 0x80,
    0x00, 0x56, 0x80, 0x00, 0x55, 0x80, 0x00, 0x55,
    0x80, 0x00, 0x55, 0x80, 0x00, 0x54, 0x80, 0x00,
    0x54, 0x80, 0x00, 0x54, 0x80, 0x00, 0x53, 0x80,
    0x00, 0x53, 0x80, 0x00, 0x53, 0x80, 0x00, 0x52,
    0x80, 0x00, 0x52, 0x80, 0x00, 0x52, 0x80, 0x00,
    0x51, 0x80, 0x00, 0x51, 0x80, 0x00, 0x51, 0x80,
    0x00, 0x51, 0x80, 0x00, 0x50, 0x80, 0x00, 0x50,
    0x80, 0x00, 0x50, 0x80, 0x00, 0x4F, 0x80, 0x00,
    0x4F, 0x80, 0x00, 0x4F, 0x80, 0x00, 0x4E, 0x80,
    0x00, 0x4E, 0x80, 0x00, 0x4E, 0x80, 0x00, 0x4D,
    0x80, 0x00, 0x4D, 0x80, 0x00, 0x4D, 0x80, 0x00,
    0x4C, 0x80, 0x00, 0x4C, 0x80, 0x00, 0x4C, 0x80,
    0x00, 0x4B, 0x80, 0x00, 0x4B, 0x80, 0x00, 0x4B,
    0x80, 0x00, 0x4A, 0x80, 0x00, 0x4A, 0x80, 0x00,
    0x4A, 0x80, 0x00, 0x49, 0x80, 0x00, 0x49, 0x80,
    0x00, 0x49, 0x80, 0x00, 0x48, 0x80, 0x00, 0x48,
    0x80, 0x00, 0x48, 0x80, 0x00, 0x47, 0x80, 0x00,
    0x47, 0x80, 0x00, 0x47, 0x80, 0x00, 0x46, 0x80,
    0x00, 0x46, 0x80, 0x00, 0x46, 0x80, 0x00, 0x45,
    0x80, 0x00, 0x45, 0x80, 0x00, 0x45, 0x80, 0x00,
    0x44, 0x80, 0x00, 0x44, 0x80, 0x00, 0x44, 0x80,
    0x00, 0x43, 0x80, 0x00, 0x43, 0x80, 0x00, 0x43,
    0x80, 0x00, 0x42, 0x80, 0x00, 0x42, 0x80, 0x00,
    0x42, 0x80, 0x00, 0x41, 0x80, 0x00, 0x41, 0x80,
    0x00, 0x41, 0x80, 0x00, 0x40, 0x80, 0x00, 0x40,
    0x80, 0x00, 0x40, 0x80, 0x00, 0x40, 0x80, 0x00,
    0x3F, 0x80, 0x00, 0x3F, 0x80, 0x00, 0x3F, 0x80,
    0x00, 0x3E, 0x80, 0x00, 0x3E, 0x80, 0x00, 0x3E,
    0x80, 0x00, 0x3D, 0x80, 0x00, 0x3D, 0x80, 0x00,
    0x3D, 0x80, 0x00, 0x3C, 0x80, 0x00, 0x3C, 0x80,
    0x00, 0x3C, 0x80, 0x00, 0x3B, 0x80, 0x00, 0x3B,
    0x80, 0x00, 0x3B, 0x80, 0x00, 0x3A, 0x80, 0x00,
    0x3A, 0x80, 0x00, 0x3A, 0x80, 0x00, 0x39, 0x80,
    0x00, 0x39, 0x80, 0x00, 0x39, 0x80, 0x00, 0x38,
    0x80, 0x00, 0x38, 0x80, 0x00, 0x38, 0x80, 0x00,
    0x37, 0x80, 0x00, 0x37, 0x80, 0x00, 0x37, 0x80,
    0x00, 0x36, 0x80, 0x00, 0x36, 0x80, 0x00, 0x36,
    0x80, 0x00, 0x35, 0x80, 0x00, 0x35, 0x80, 0x00,
    0x35, 0x80, 0x00, 0x34, 0x80, 0x00, 0x34, 0x80,
    0x00, 0x34, 0x80, 0x00, 0x33, 0x80, 0x00, 0x33,
    0x80, 0x00, 0x33, 0x80, 0x00, 0x32, 0x80, 0x00,
    0x32, 0x80, 0x00, 0x32, 0x80, 0x00, 0x31, 0x80,
    0x00, 0x31, 0x80, 0x00, 0x31, 0x80, 0x00, 0x30,
    0x80, 0x00, 0x30, 0x80, 0x00, 0x30, 0x80, 0x00,
    0x2F, 0x80, 0x00, 0x2F, 0x80, 0x00, 0x2F, 0x80,
    0x00, 0x2E, 0x80, 0x00, 0x2E, 0x80, 0x00, 0x2E,
    0x80, 0x00, 0x2D, 0x80, 0x00, 0x2D, 0x80, 0x00,
    0x2D, 0x80, 0x00, 0x2C, 0x80, 0x00, 0x2C, 0x80,
    0x00, 0x2C, 0x80, 0x00, 0x2B, 0x80, 0x00, 0x2B,
    0x80, 0x00, 0x2B, 0x80, 0x00, 0x2A, 0x80, 0x00,
    0x2A, 0x80, 0x00, 0x2A, 0x80, 0x00, 0x29, 0x80,
    0x00, 0x29, 0x80, 0x00, 0x29, 0x80, 0x00, 0x28,
    0x80, 0x00, 0x28, 0x80, 0x00, 0x28, 0x80, 0x00,
    0x27, 0x80, 0x00, 0x27, 0x80, 0x00, 0x27, 0x80,
    0x00, 0x26, 0x80, 0x00, 0x26, 0x80, 0x00, 0x26,
    0x80, 0x00, 0x25, 0x80, 0x00, 0x25, 0x80, 0x00,
    0x25, 0x80, 0x00, 0x24, 0x80, 0x00, 0x24, 0x80,
    0x00, 0x24, 0x80, 0x00, 0x24, 0x80, 0x00, 0x23,
    0x80, 0x00, 0x23, 0x80, 0x00, 0x23, 0x80, 0x00,
    0x22, 0x80, 0x00, 0x22, 0x80, 0x00, 0x22, 0x80,
    0x00, 0x21, 0x80, 0x00, 0x21, 0x80, 0x00, 0x21,
    0x80, 0x00, 0x20, 0x80, 0x00, 0x20, 0x80, 0x00,
    0x20, 0x80, 0x00, 0x1F, 0x80, 0x00, 0x1F, 0x80,
    0x00, 0x1F, 0x80, 0x00, 0x1E, 0x80, 0x00, 0x1E,
    0x80, 0x00, 0x1E, 0x80, 0x00, 0x1D, 0x80, 0x00,
    0x1D, 0x80, 0x00, 0x1D, 0x80, 0x00, 0x1C, 0x80,
    0x00, 0x1C, 0x80, 0x00, 0x1C, 0x80, 0x00, 0x1B,
    0x80, 0x00, 0x1B, 0x80, 0x00, 0x1B, 0x80, 0x00,
    0x1A, 0x80, 0x00, 0x1A, 0x80, 0x00, 0x1A, 0x80,
    0x00, 0x19, 0x80, 0x00, 0x19, 0x80, 0x00, 0x19,
    0x80, 0x00, 0x18, 0x80, 0x00, 0x18, 0x80, 0x00,
    0x18, 0x80, 0x00, 0x17, 0x80, 0x00, 0x17, 0x80,
    0x00, 0x17, 0x80, 0x00, 0x16, 0x80, 0x00, 0x16,
    0x80, 0x00, 0x16, 0x80, 0x00, 0x15, 0x80, 0x00,
    0x15, 0x80, 0x00, 0x15, 0x80, 0x00, 0x14, 0x80,
    0x00, 0x14, 0x80, 0x00, 0x14, 0x80, 0x00, 0x13,
    0x80, 0x00, 0x13, 0x80, 0x00, 0x13, 0x80, 0x00,
    0x12, 0x80, 0x00, 0x12, 0x80, 0x00, 0x12, 0x80,
    0x00, 0x11, 0x80, 0x00, 0x11, 0x80, 0x00, 0x11,
    0x80, 0x00, 0x10, 0x80, 0x00, 0x10, 0x80, 0x00,
    0x10, 0x80, 0x00, 0x0F, 0x80, 0x00, 0x0F, 0x80,
    0x00, 0x0F, 0x80, 0x00, 0x0E, 0x80, 0x00, 0x0E,
    0x80, 0x00, 0x0E, 0x80, 0x00, 0x0D, 0x80, 0x00,
    0x0D, 0x80, 0x00, 0x0D, 0x80, 0x00, 0x0C, 0x80,
    0x00, 0x0C, 0x80, 0x00, 0x0C, 0x80, 0x00, 0x0B,
    0x80, 0x00, 0x0B, 0x80, 0x00, 0x0B, 0x80, 0x00,
    0x0A, 0x80, 0x00, 0x0A, 0x80, 0x00, 0x0A, 0x80,
    0x00, 0x09, 0x80, 0x00, 0x09, 0x80, 0x00, 0x09,
    0x80, 0x00, 0x09, 0x80, 0x00, 0x08, 0x80, 0x00,
    0x08, 0x80, 0x00, 0x08, 0x80, 0x00, 0x07, 0x80,
    0x00, 0x07, 0x80, 0x00, 0x07, 0x80, 0x00, 0x06,
    0x80, 0x00, 0x06, 0x80, 0x00, 0x06, 0x80, 0x00,
    0x05, 0x80, 0x00, 0x05, 0x80, 0x00, 0x05, 0x80,
    0x00, 0x04, 0x80, 0x00, 0x04, 0x80, 0x00, 0x04,
    0x80, 0x00, 0x03, 0x80, 0x00, 0x03, 0x80, 0x00,
    0x03, 0x80, 0x00, 0x02, 0x80, 0x00, 0x02, 0x80,
    0x00, 0x02, 0x80, 0x00, 0x01, 0x80, 0x00, 0x01,
    0x80, 0x00, 0x01, 0x80, 0x00, 0x00, 0x80, 0x00,
    0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
    0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x81, 0x00, 0x00, 0x81, 0x00,
    0x00, 0x81, 0x00, 0x00, 0x81, 0x00, 0x00, 0x81,
    0x00, 0x00, 0x81, 0x00, 0x00, 0x82, 0x00, 0x00,
    0x82, 0x00, 0x00, 0x82, 0x00, 0x00, 0x82, 0x00,
    0x00, 0x82, 0x00, 0x00, 0x83, 0x00, 0x00, 0x83,
    0x00, 0x00, 0x83, 0x00, 0x00, 0x83, 0x00, 0x00,
    0x83, 0x00, 0x00, 0x84, 0x00, 0x00, 0x84, 0x00,
    0x00, 0x84, 0x00, 0x00, 0x84, 0x00, 0x00, 0x84,
    0x00, 0x00, 0x84, 0x00, 0x00, 0x85, 0x00, 0x00,
    0x85, 0x00, 0x00, 0x85, 0x00, 0x00, 0x85, 0x00,
    0x00, 0x85, 0x00, 0x00, 0x86, 0x00, 0x00, 0x86,
    0x00, 0x00, 0x86, 0x00, 0x00, 0x86, 0x00, 0x00,
    0x86, 0x00, 0x00, 0x86, 0x00, 0x00, 0x87, 0x00,
    0x00, 0x87, 0x00, 0x00, 0x87, 0x00, 0x00, 0x87,
    0x00, 0x00, 0x87, 0x00, 0x00, 0x88, 0x00, 0x00,
    0x88, 0x00, 0x00, 0x88, 0x00, 0x00, 0x88, 0x00,
    0x00, 0x88, 0x00, 0x00, 0x88, 0x00, 0x00, 0x89,
    0x00, 0x00, 0x89, 0x00, 0x00, 0x89, 0x00, 0x00,
    0x89, 0x00, 0x00, 0x89, 0x00, 0x00, 0x8A, 0x00,
    0x00, 0x8A, 0x00, 0x00, 0x8A, 0x00, 0x00, 0x8A,
    0x00, 0x00, 0x8A, 0x00, 0x00, 0x8B, 0x00, 0x00,
    0x8B, 0x00, 0x00, 0x8B, 0x00, 0x00, 0x8B, 0x00,
    0x00, 0x8B, 0x00, 0x00, 0x8B, 0x00, 0x00, 0x8C,
    0x00, 0x00, 0x8C, 0x00, 0x00, 0x8C, 0x00, 0x00,
    0x8C, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x8D, 0x00,
    0x00, 0x8D, 0x00, 0x00, 0x8D, 0x00, 0x00, 0x8D,
    0x00, 0x00, 0x8D, 0x00, 0x00, 0x8D, 0x00, 0x00,
    0x8E, 0x00, 0x00, 0x8E, 0x00, 0x00, 0x8E, 0x00,
    0x00, 0x8E, 0x00, 0x00, 0x8E, 0x00, 0x00, 0x8F,
    0x00, 0x00, 0x8F, 0x00, 0x00, 0x8F, 0x00, 0x00,
    0x8F, 0x00, 0x00, 0x8F, 0x00, 0x00, 0x90, 0x00,
    0x00, 0x90, 0x00, 0x00, 0x90, 0x00, 0x00, 0x90,
    0x00, 0x00, 0x90, 0x00, 0x00, 0x90, 0x00, 0x00,
    0x91, 0x00, 0x00, 0x91, 0x00, 0x00, 0x91, 0x00,
    0x00, 0x91, 0x00, 0x00, 0x91, 0x00, 0x00, 0x92,
    0x00, 0x00, 0x92, 0x00, 0x00, 0x92, 0x00, 0x00,
    0x92, 0x00, 0x00, 0x92, 0x00, 0x00, 0x92, 0x00,
    0x00, 0x93, 0x00, 0x00, 0x93, 0x00, 0x00, 0x93,
    0x00, 0x00, 0x93, 0x00, 0x00, 0x93, 0x00, 0x00,
    0x94, 0x00, 0x00, 0x94, 0x00, 0x00, 0x94, 0x00,
    0x00, 0x94, 0x00, 0x00, 0x94, 0x00, 0x00, 0x94,
    0x00, 0x00, 0x95, 0x00, 0x00, 0x95, 0x00, 0x00,
    0x95, 0x00, 0x00, 0x95, 0x00, 0x00, 0x95, 0x00,
    0x00, 0x96, 0x00, 0x00, 0x96, 0x00, 0x00, 0x96,
    0x00, 0x00, 0x96, 0x00, 0x00, 0x96, 0x00, 0x00,
    0x97, 0x00, 0x00, 0x97, 0x00, 0x00, 0x97, 0x00,
    0x00, 0x97, 0x00, 0x00, 0x97, 0x00, 0x00, 0x97,
    0x00, 0x00, 0x98, 0x00, 0x00, 0x98, 0x00, 0x00,
    0x98, 0x00, 0x00, 0x98, 0x00, 0x00, 0x98, 0x00,
    0x00, 0x99, 0x00, 0x00, 0x99, 0x00, 0x00, 0x99,
    0x00, 0x00, 0x99, 0x00, 0x00, 0x99, 0x00, 0x00,
    0x99, 0x00, 0x00, 0x9A, 0x00, 0x00, 0x9A, 0x00,
    0x00, 0x9A, 0x00, 0x00, 0x9A, 0x00, 0x00, 0x9A,
    0x00, 0x00, 0x9B, 0x00, 0x00, 0x9B, 0x00, 0x00,
    0x9B, 0x00, 0x00, 0x9B, 0x00, 0x00, 0x9B, 0x00,
    0x00, 0x9C, 0x00, 0x00, 0x9C, 0x00, 0x00, 0x9C,
    0x00, 0x00, 0x9C, 0x00, 0x00, 0x9C, 0x00, 0x00,
    0x9C, 0x00, 0x00, 0x9D, 0x00, 0x00, 0x9D, 0x00,
    0x00, 0x9D, 0x00, 0x00, 0x9D, 0x00, 0x00, 0x9D,
    0x00, 0x00, 0x9E, 0x00, 0x00, 0x9E, 0x00, 0x00,
    0x9E, 0x00, 0x00, 0x9E, 0x00, 0x00, 0x9E, 0x00,
    0x00, 0x9E, 0x00, 0x00, 0x9F, 0x00, 0x00, 0x9F,
    0x00, 0x00, 0x9F, 0x00, 0x00, 0x9F, 0x00, 0x00,
    0x9F, 0x00, 0x00, 0xA0, 0x00, 0x00, 0xA0, 0x00,
    0x00, 0xA0, 0x00, 0x00, 0xA0, 0x00, 0x00, 0xA0,
    0x00, 0x00, 0xA0, 0x00, 0x00, 0xA0, 0x00, 0x00,
    0xA1, 0x00, 0x00, 0xA1, 0x00, 0x00, 0xA1, 0x00,
    0x00, 0xA1, 0x00, 0x00, 0xA1, 0x00, 0x00, 0xA1,
    0x00, 0x00, 0xA2, 0x00, 0x00, 0xA2, 0x00, 0x00,
    0xA2, 0x00, 0x00, 0xA2, 0x00, 0x00, 0xA2, 0x00,
    0x00, 0xA3, 0x00, 0x00, 0xA3, 0x00, 0x00, 0xA3,
    0x00, 0x00, 0xA3, 0x00, 0x00, 0xA3, 0x00, 0x00,
    0xA3, 0x00, 0x00, 0xA4, 0x00, 0x00, 0xA4, 0x00,
    0x00, 0xA4, 0x00, 0x00, 0xA4, 0x00, 0x00, 0xA4,
    0x00, 0x00, 0xA4, 0x00, 0x00, 0xA5, 0x00, 0x00,
    0xA5, 0x00, 0x00, 0xA5, 0x00, 0x00, 0xA5, 0x00,
    0x00, 0xA5, 0x00, 0x00, 0xA5, 0x00, 0x00, 0xA6,
    0x00, 0x00, 0xA6, 0x00, 0x00, 0xA6, 0x00, 0x00,
    0xA6, 0x00, 0x00, 0xA6, 0x00, 0x00, 0xA7, 0x00,
    0x00, 0xA7, 0x00, 0x00, 0xA7, 0x00, 0x00, 0xA7,
    0x00, 0x00, 0xA7, 0x00, 0x00, 0xA7, 0x00, 0x00,
    0xA8, 0x00, 0x00, 0xA8, 0x00, 0x00, 0xA8, 0x00,
    0x00, 0xA8, 0x00, 0x00, 0xA8, 0x00, 0x00, 0xA8,
    0x00, 0x00, 0xA9, 0x00, 0x00, 0xA9, 0x00, 0x00,
    0xA9, 0x00, 0x00, 0xA9, 0x00, 0x00, 0xA9, 0x00,
    0x00, 0xAA, 0x00, 0x00, 0xAA, 0x00, 0x00, 0xAA,
    0x00, 0x00, 0xAA, 0x00, 0x00, 0xAA, 0x00, 0x00,
    0xAA, 0x00, 0x00, 0xAB, 0x00, 0x00, 0xAB, 0x00,
    0x00, 0xAB, 0x00, 0x00, 0xAB, 0x00, 0x00, 0xAB,
    0x00, 0x00, 0xAB, 0x00, 0x00, 0xAC, 0x00, 0x00,
    0xAC, 0x00, 0x00, 0xAC, 0x00, 0x00, 0xAC, 0x00,
    0x00, 0xAC, 0x00, 0x00, 0xAC, 0x00, 0x00, 0xAD,
    0x00, 0x00, 0xAD, 0x00, 0x00, 0xAD, 0x00, 0x00,
    0xAD, 0x00, 0x00, 0xAD, 0x00, 0x00, 0xAE, 0x00,
    0x00, 0xAE, 0x00, 0x00, 0xAE, 0x00, 0x00, 0xAE,
    0x00, 0x00, 0xAE, 0x00, 0x00, 0xAE, 0x00, 0x00,
    0xAF, 0x00, 0x00, 0xAF, 0x00, 0x00, 0xAF, 0x00,
    0x00, 0xAF, 0x00, 0x00, 0xAF, 0x00, 0x00, 0xAF,
    0x00, 0x00, 0xB0, 0x00, 0x00, 0xB0, 0x00, 0x00,
    0xB0, 0x00, 0x00, 0xB0, 0x00, 0x00, 0xB0, 0x00,
    0x00, 0xB0, 0x00, 0x00, 0xB1, 0x00, 0x00, 0xB1,
    0x00, 0x00, 0xB1, 0x00, 0x00, 0xB1, 0x00, 0x00,
    0xB1, 0x00, 0x00, 0xB2, 0x00, 0x00, 0xB2, 0x00,
    0x00, 0xB2, 0x00, 0x00, 0xB2, 0x00, 0x00, 0xB2,
    0x00, 0x00, 0xB2, 0x00, 0x00, 0xB3, 0x00, 0x00,
    0xB3, 0x00, 0x00, 0xB3, 0x00, 0x00, 0xB3, 0x00,
    0x00, 0xB3, 0x00, 0x00, 0xB3, 0x00, 0x00, 0xB4,
    0x00, 0x00, 0xB4, 0x00, 0x00, 0xB4, 0x00, 0x00,
    0xB4, 0x00, 0x00, 0xB4, 0x00, 0x00, 0xB5, 0x00,
    0x00, 0xB5, 0x00, 0x00, 0xB5, 0x00, 0x00, 0xB5,
    0x00, 0x00, 0xB5, 0x00, 0x00, 0xB5, 0x00, 0x00,
    0xB6, 0x00, 0x00, 0xB6, 0x00, 0x00, 0xB6, 0x00,
    0x00, 0xB6, 0x00, 0x00, 0xB6, 0x00, 0x00, 0xB6,
    0x00, 0x00, 0xB7, 0x00, 0x00, 0xB7, 0x00, 0x00,
    0xB7, 0x00, 0x00, 0xB7, 0x00, 0x00, 0xB7, 0x00,
    0x00, 0xB7, 0x00, 0x00, 0xB8, 0x00, 0x00, 0xB8,
    0x00, 0x00, 0xB8, 0x00, 0x00, 0xB8, 0x00, 0x00,
    0xB8, 0x00, 0x00, 0xB9, 0x00, 0x00, 0xB9, 0x00,
    0x00, 0xB9, 0x00, 0x00, 0xB9, 0x00, 0x00, 0xB9,
    0x00, 0x00, 0xB9, 0x00, 0x00, 0xBA, 0x00, 0x00,
    0xBA, 0x00, 0x00, 0xBA, 0x00, 0x00, 0xBA, 0x00,
    0x00, 0xBA, 0x00, 0x00, 0xBA, 0x00, 0x00, 0xBB,
    0x00, 0x00, 0xBB, 0x00, 0x00, 0xBB, 0x00, 0x00,
    0xBB, 0x00, 0x00, 0xBB, 0x00, 0x00, 0xBB, 0x00,
    0x00, 0xBC, 0x00, 0x00, 0xBC, 0x00, 0x00, 0xBC,
    0x00, 0x00, 0xBC, 0x00, 0x00, 0xBC, 0x00, 0x00,
    0xBD, 0x00, 0x00, 0xBD, 0x00, 0x00, 0xBD, 0x00,
    0x00, 0xBD, 0x00, 0x00, 0xBD, 0x00, 0x00, 0xBD,
    0x00, 0x00, 0xBE, 0x00, 0x00, 0xBE, 0x00, 0x00,
    0xBE, 0x00, 0x00, 0xBE, 0x00, 0x00, 0xBE, 0x00,
    0x00, 0xBE, 0x00, 0x00, 0xBF, 0x00, 0x00, 0xBF,
    0x00, 0x00, 0xBF, 0x00, 0x00, 0xBF, 0x00, 0x00,
    0xBF, 0x00, 0x00, 0xC0, 0x00, 0x00, 0xC0, 0x00,
};

// This function does any needed initialization on the rendering
// context. 
void SetupRC(void)
{
    // Background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

    glEnable(GL_DEPTH_TEST);

    viewFrame.MoveForward(-155.0f);
    viewFrame.MoveUp(20.0f);

    grassShader = gltLoadShaderPairWithAttributes("Grass.vs", "Grass.fs",
                                                        1,
                                                        GLT_ATTRIBUTE_VERTEX, "vVertex");

    locMVP = glGetUniformLocation(grassShader, "mvpMatrix");

    glUseProgram(grassShader);
    glUniform1i(glGetUniformLocation(grassShader, "length_texture"), 0);
    glUniform1i(glGetUniformLocation(grassShader, "orientation_texture"), 1);
    glUniform1i(glGetUniformLocation(grassShader, "grasspalette_texture"), 2);
    glUniform1i(glGetUniformLocation(grassShader, "grasscolor_texture"), 3);
    glUniform1i(glGetUniformLocation(grassShader, "bend_texture"), 4);

    static const GLfloat grass_blade[] =
    {
        -0.3f, 0.0f,
         0.3f, 0.0f,
        -0.20f, 1.0f,
         0.1f, 1.3f,
        -0.05f, 2.3f,
         0.0f, 3.3f
    };

    // Greate a vertex array object and a vertex buffer for the quad
    // including position and texture coordinates
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(grass_blade), grass_blade, GL_STATIC_DRAW);
    glVertexAttribPointer(GLT_ATTRIBUTE_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(GLT_ATTRIBUTE_VERTEX);

    // 
    glGenTextures(1, &length_texture);
    glBindTexture(GL_TEXTURE_2D, length_texture);
    GLint w, h, c;
    GLenum f;
    void * bits = gltReadTGABits("length.tga", &w, &h, &c, &f);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, bits);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    free(bits);

    glGenTextures(1, &orientation_texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, orientation_texture);
    bits = gltReadTGABits("orientation.tga", &w, &h, &c, &f);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, bits);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    free(bits);

    glGenTextures(1, &grasspalette_texture);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_1D, grasspalette_texture);
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB8, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, grasspalette_data);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

    glGenTextures(1, &grasscolor_texture);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, grasscolor_texture);
    bits = gltReadTGABits("color.tga", &w, &h, &c, &f);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, bits);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    free(bits);

    glGenTextures(1, &bend_texture);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, bend_texture);
    bits = gltReadTGABits("bend.tga", &w, &h, &c, &f);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, bits);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    free(bits);
}

// Cleanup
void ShutdownRC(void)
{
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &vao);
}

// Called to draw scene
void RenderScene(void)
{
    static CStopWatch rotTimer;

    // Clear the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    modelViewMatrix.PushMatrix(viewFrame);
    modelViewMatrix.Translate(0.0f, 0.0f, 800.0f);
    modelViewMatrix.Rotate(-12.0, 1.0f, 0.0f, 0.0f);
    modelViewMatrix.Rotate(rotTimer.GetElapsedSeconds() * 15.0f, 0.0f, 1.0f, 0.0f);

    glUseProgram(grassShader);
    glUniformMatrix4fv(locMVP, 1, GL_FALSE, transformPipeline.GetModelViewProjectionMatrix());

    glBindVertexArray(vao);

    glDrawArraysInstancedARB(GL_TRIANGLE_STRIP, 0, 6, 1024 * 1024);

    modelViewMatrix.PopMatrix();

    glutSwapBuffers();
    glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
    // Prevent a divide by zero
    if(h == 0)
        h = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    viewFrustum.SetPerspective(35.0f, float(w)/float(h), 1.0f, 3000.0f);

    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
}

void Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        // Space toggles perspective correction
        default:
            break;
    };
}

///////////////////////////////////////////////////////////////////////////////
// Main entry point for GLUT based programs
int main(int argc, char* argv[])
{
    gltSetWorkingDirectory(argv[0]);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitContextVersion(3, 2);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Grass");
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(Keyboard);
    glutDisplayFunc(RenderScene);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
        return 1;
    }

    SetupRC();

    glutMainLoop();
    ShutdownRC();

    return 0;
}
