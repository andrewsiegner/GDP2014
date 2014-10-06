#include "global.h"

glm::mat4 g_matProjection = glm::mat4(1.0f);	// 1.0f gives identity matrix
glm::mat4 g_matView = glm::mat4(1.0f);
glm::mat4 g_matWorld = glm::mat4(1.0f);		// aka "Model" matrix

GLuint g_ProjectionMatrixUniformLocation = 0;			
GLuint g_ViewMatrixUniformLocation = 0;				
GLuint g_ModelMatrixUniformLocation = 0;				
GLuint g_ObjectColourUniformLocation = 0;				

GLuint g_slot_LightPosition = 0;	//uniform vec4 LightPosition;	
GLuint g_slot_LightColour = 0;	//uniform vec4 LightColour;		
GLuint g_slot_attenuation = 0;	//uniform float attenuation;	


// Same sort of thing as the "name" of the buffer, but these are the 
// "names" of the shaders we are loading
//GLuint g_ShaderIds[3] = { 0 };		
// Or these might be a little more clear...
GLuint g_ShaderProgram_ID = 0;
GLuint g_VertexShader_ID = 0;
GLuint g_FragmentShader_ID = 0;

// ***********************************************
// *** WE'LL BE MOVING THIS STUFF OUT OF HERE ****
int g_numberOfTriangles[2] = {0}; 
GLuint g_VertexPositionBufferID[2] = {0};		// BufferIds[0]		
GLuint g_VertexColourBufferID[2] = {0};			// BufferIds[1]		
GLuint g_IndexBufferID[2] = {0};					// BufferIds[2]		
// ***********************************************


CModelLoaderManager*  g_pModelLoader = 0;	// set pointers to zero just in case