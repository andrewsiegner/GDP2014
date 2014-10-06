#ifndef _global_HG_
#define _global_HG_

#include "Utils.h"		// Contains Vertex struct

#include "CGameObject.h"				// Moved to global.h
#include "CTriangle.h"		

#define GLM_FORCE_CXX98    
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp> // glm::mat4

// Added on October 2, 2014 
#include "CModelLoaderManager.h"
extern CModelLoaderManager*  g_pModelLoader;	// "p" for pointer


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
extern int g_numberOfTriangles[2]; 
extern GLuint g_VertexPositionBufferID[2];			// BufferIds[0]		
extern GLuint g_VertexColourBufferID[2];			// BufferIds[1]		
extern GLuint g_IndexBufferID[2];					// BufferIds[2]		
// ***********************************************
				
#endif
