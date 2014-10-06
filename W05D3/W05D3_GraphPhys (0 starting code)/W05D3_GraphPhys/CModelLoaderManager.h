#ifndef _CModelLoaderManager_HG_
#define _CModelLoaderManager_HG_

// This AMAZING class will do the following:
// * Load models from files
// * Place the model information into the sexy OpenGL VBOs+Buffers
// * Keep track (for looking up) model to drawing data

#include <vector>
#include <string>
#include "CPlyInfo.h"
// NOTE: I took these out as the CFactory was including this file, and I didn't want OpenGL stuff all over the place
//#include <GL\glxew.h>		// From the OpenGL site
//#include <GL\glew.h>
//#include <GL\freeglut.h>	

// Could use "Pointer to implementation" (p-pl) pattern
#include "CTriangle.h"		// Because the private methods need it


class CModelLoaderManager
{
public:
	CModelLoaderManager();
	~CModelLoaderManager();
	bool LoadModels( std::vector< std::string > vecFileNames );

	bool GetRenderingInfoByModelFileName( std::string modelName, 
		                                  CPlyInfo &theInfo );
private:
	std::vector< CPlyInfo > m_VecModels;

	// SECRET functions only this class my call...
	// Update: took out the GLuint, replaced with "unsigned int"
	bool m_LoadPlyFileIntoGLBuffers( std::string plyFile,
							         unsigned int &vertexBufferID,			/* GLuint &vertexBufferID, */
							         unsigned int &vertexColourBufferID,	/* GLuint &vertexColourBufferID, */
							         unsigned int &indexBufferID,			/* GLuint &indexBufferID, */
							         int &numberOfVerticesLoaded, 
							         int &numberOfTrianglesLoaded, 
							         float &maxExtent );

	bool m_LoadPlyFile(std::string plyFileName, 
				 std::vector<CVertex> &vecVertices, 
				 std::vector<CTriangle> &vecTriangles );
};

#endif
