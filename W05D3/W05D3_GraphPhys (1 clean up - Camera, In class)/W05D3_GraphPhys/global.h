#ifndef _global_HG_
#define _global_HG_

//#include "Utils.h"		// Contains Vertex struct, but no longer neededd
#include <time.h>			// Only needed for the "clock_t g_LastTime" variable

#define GLM_FORCE_CXX98    
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp> // glm::mat4

#include "CGameObject.h"				
#include "CTriangle.h"		
#include "CFactoryMediator.h"	
#include "CModelLoaderManager.h"

// ADDED October 3, 2014
#include "CCamera.h"

extern CCamera* g_pCamera;

extern CModelLoaderManager*  g_pModelLoader;	// "p" for pointer

extern CFactoryMediator* g_pFactoryMediator;			
extern unsigned int g_Player_ID;	// = 0;		// Used to locate the player




extern glm::mat4 g_matProjection;
extern glm::mat4 g_matView;
extern glm::mat4 g_matWorld;		// aka "Model" matrix

extern GLuint g_ProjectionMatrixUniformLocation;			
extern GLuint g_ViewMatrixUniformLocation;				
extern GLuint g_ModelMatrixUniformLocation;				
extern GLuint g_ObjectColourUniformLocation;				

extern GLuint g_slot_LightPosition;	//uniform vec4 LightPosition;	
extern GLuint g_slot_LightColour;	//uniform vec4 LightColour;		
extern GLuint g_slot_attenuation;	//uniform float attenuation;	

// Same sort of thing as the "name" of the buffer, but these are the 
// "names" of the shaders we are loading
//extern GLuint g_ShaderIds[3];// = { 0 };		
// or these might be a little more clear...
extern GLuint g_ShaderProgram_ID;
extern GLuint g_VertexShader_ID;
extern GLuint g_FragmentShader_ID;

extern int g_screenWidth;	// = 1400;
extern int g_screenHeight;	// = 900;
extern int g_windowHandle;	// = 0;
extern unsigned int g_FrameCount;	// = 0;
extern clock_t g_LastTime;		// = 0;		

// Since this is static (i.e. there's only one of these), so we don't need "extern"
static const std::string g_WindowTitleDefault = "OpenGL for the win!";

bool SetShaderUniformVariables(void);

bool LoadPlyFileIntoGLBuffers( std::string plyFile,
							   GLuint &vertexBufferID, 
							   GLuint &vertexColourBufferID, 
							   GLuint &indexBufferID, 
							   int &numberOfVerticesLoaded, 
							   int &numberOfTrianglesLoaded, 
							   float &maxExtent );


// ***********************************************
// *** WE'LL BE MOVING THIS STUFF OUT OF HERE ****
//extern int g_numberOfTriangles[2]; 
//extern GLuint g_VertexPositionBufferID[2];			// BufferIds[0]		
//extern GLuint g_VertexColourBufferID[2];			// BufferIds[1]		
//extern GLuint g_IndexBufferID[2];					// BufferIds[2]		
// ***********************************************

bool OpenGL_Initialize(int argc, char* argv[], int screenWidth, int screenHeight);

// OpenGL callbacks
void glutReshape_callback(int Width, int Height);		// void ResizeFunction(int, int);
void glutDisplay_callback(void);						// void RenderFunction(void);
void TimerFunction(int);
void IdleFunction(void);
void glutClose_callback(void);							// void DestroyCube(void);

// ADDED in class on September 19, 2014
void glutKeyboard_callback(unsigned char key, int x, int y);	// void keyboardFunctionCallback(unsigned char key, int x, int y);
void glutSpecialKey_callback( int key, int x, int y );			// void specialKeyCallback( int key, int x, int y );

// Moved from Util.cpp (we'll be replacing this at some point...
// ...having a function exit on its own might not be a good idea)
void ExitOnGLError(const char* error_message);						// from Util.cpp
GLuint LoadShader(const char* filename, GLenum shader_type);		// from Util.cpp

static const double PI = 3.14159265358979323846;		// Was in Util.h, but super helpful, yo!

				
#endif
