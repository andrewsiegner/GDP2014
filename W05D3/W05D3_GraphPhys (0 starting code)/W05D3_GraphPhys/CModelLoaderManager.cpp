#include "CModelLoaderManager.h"

#include "CTriangle.h"		// also includes CVertex
#include <fstream>			// For loading the files ifstream

#include "Utils.h"			// the "Vertex" class

bool CModelLoaderManager::m_LoadPlyFile(std::string plyFileName, 
				                        std::vector<CVertex> &vecVertices, 
				                        std::vector<CTriangle> &vecTriangles )
{
	int numberOfVerticesToLoad = 0;
	int numberOfTrianglesToLoad = 0;

	vecVertices.clear();
	vecTriangles.clear();

	std::wifstream myFile( plyFileName.c_str() );
	//std::wifstream myFile("Utah_Teapot.ply");
	if ( ! myFile.is_open() )	
	{
		return false;
	}

	// Read everything up to the word "vertex"
	std::wstring temp;
	bool bKeepReading = true;
	while ( bKeepReading )
	{
		myFile >> temp;				// Read next "string" into temp
		if ( temp == L"vertex" )	
		{
			bKeepReading = false;
		}
	};
	// Next value is number of vertices
	myFile >> numberOfVerticesToLoad;

	// Same thing, but number of triangles (aka "elements")
	bKeepReading = true;
	while ( bKeepReading )
	{
		myFile >> temp;
		if ( temp == L"face" )	
		{
			bKeepReading = false;
		}
	};
	// Next value is number of vertices
	myFile >> numberOfTrianglesToLoad;

	// Same thing, but look for 
	bKeepReading = true;
	while ( bKeepReading )
	{
		myFile >> temp;
		if ( temp == L"end_header" )	
		{
			bKeepReading = false;
		}
	};

	// Now, I can read the actual information... 
	for ( int count = 0; count != numberOfVerticesToLoad; count++ )
	{
		CVertex tempVert;
		myFile >> tempVert.x >> tempVert.y >> tempVert.z;

		// *** NOTE: the original files have x,y,z, followed by "confidence" and "intensity"
		//// Extra two numbers. Read and discard;
		//float temp;
		//myFile >> temp >> temp;

		vecVertices.push_back( tempVert );
	}

	// 
	for ( int count = 0; count != numberOfTrianglesToLoad; count++ )
	{
		CTriangle tempTri;
		int discard;
		// 3 564 612 611 
		myFile >> discard >> tempTri.V1 >> tempTri.V2 >> tempTri.V3;

		vecTriangles.push_back( tempTri );
	}

	myFile.close();  // It's nice to be nice. Close the file.

	return true;
}


bool CModelLoaderManager::m_LoadPlyFileIntoGLBuffers( std::string plyFile,
							   unsigned int &vertexBufferID,					/* GLuint &vertexBufferID, */
							   unsigned int &vertexColourBufferID,				/* GLuint &vertexColourBufferID, */
							   unsigned int &indexBufferID,						/* GLuint &indexBufferID, */
							   int &numberOfVerticesLoaded, 
							   int &numberOfTrianglesLoaded, 
							   float &maxExtent )
{
	std::vector<CVertex>   vecVertices;
	std::vector<CTriangle> vecTriangles;


	if ( ! this->m_LoadPlyFile( plyFile, vecVertices, vecTriangles ) ) 
	{
		return false;
	}

	// Determine the maximum extent
	// Assume the min and max are the first vertex, to start
	float minX = vecVertices[0].x;	
	float maxX = vecVertices[0].x;
	float minY = vecVertices[0].y;	
	float maxY = vecVertices[0].y;
	float minZ = vecVertices[0].z;	
	float maxZ = vecVertices[0].z;
	for ( int index = 0; index != (int)vecVertices.size(); index++ )
	{
		if ( vecVertices[index].x > maxX ) { maxX = vecVertices[index].x; }
		if ( vecVertices[index].x < minX ) { minX = vecVertices[index].x; }
		if ( vecVertices[index].y > maxY ) { maxY = vecVertices[index].y; }
		if ( vecVertices[index].y < minY ) { minY = vecVertices[index].y; }
		if ( vecVertices[index].z > maxZ ) { maxZ = vecVertices[index].z; }
		if ( vecVertices[index].z < minZ ) { minZ = vecVertices[index].z; }
	}
	float extentX = abs( maxX - minX );
	float extentY = abs( maxY - minY );
	float extentZ = abs( maxZ - minZ );

	maxExtent = extentX;
	if ( extentY > maxExtent ) { maxExtent = extentY; }
	if ( extentZ > maxExtent ) { maxExtent = extentZ; }
	

	// Create a dynamic array to hold vertices...
	numberOfVerticesLoaded = static_cast<int>( vecVertices.size() );
	Vertex* p_arrayBunnyVertices = new Vertex[ numberOfVerticesLoaded ];
	// Copy the data from the bunny vector to this array
	for ( int vertIndex = 0; vertIndex != numberOfVerticesLoaded; vertIndex++ )
	{
		p_arrayBunnyVertices[vertIndex].Position[0]  = vecVertices[vertIndex].x;
		p_arrayBunnyVertices[vertIndex].Position[1]  = vecVertices[vertIndex].y;
		p_arrayBunnyVertices[vertIndex].Position[2]  = vecVertices[vertIndex].z;
		p_arrayBunnyVertices[vertIndex].Position[3]  = 1.0f;		// 4th should be 1.0 if not sure
		// There is also colour values per vertex
		p_arrayBunnyVertices[vertIndex].Color[0] = 1.0f;		// Red
		p_arrayBunnyVertices[vertIndex].Color[1] = 1.0f;		// Green
		p_arrayBunnyVertices[vertIndex].Color[2] = 1.0f;		// Blue
		p_arrayBunnyVertices[vertIndex].Color[3] = 1.0f;		// Alpha
	}

	// Each triangle has three corners, so we need 3 X number of triangles == number of indices
	numberOfTrianglesLoaded = static_cast<int>( vecTriangles.size() );
	int numberOfIndices = numberOfTrianglesLoaded * 3;

	// **************************************************************************************
	GLuint* p_bunnyIndices = new GLuint[ numberOfIndices ];
	//GLuint p_bunnyIndices[3851 * 3];

	for ( int triIndex = 0; triIndex < numberOfTrianglesLoaded; triIndex++ )	// Step by three
	{
		CTriangle tempTri = vecTriangles[triIndex];
	  
		int index1 = (triIndex * 3);
		int index2 = (triIndex * 3) + 1;
		int index3 = (triIndex * 3) + 2;

		p_bunnyIndices[index1] = (GLuint)tempTri.V1;
		p_bunnyIndices[index2] = (GLuint)tempTri.V2;
		p_bunnyIndices[index3] = (GLuint)tempTri.V3;
		//p_bunnyIndices[(triIndex * 3) + 0] = (GLuint)g_vecTriangles[triIndex].V1;
		//p_bunnyIndices[(triIndex * 3) + 1] = (GLuint)g_vecTriangles[triIndex].V2;
		//p_bunnyIndices[(triIndex * 3) + 2] = (GLuint)g_vecTriangles[triIndex].V3;
	}

	// Now set up the OpenGL buffers and copy the information over

	// Get an ID (aka "name") for the two-part vertex buffer
	glGenVertexArrays(1, &vertexBufferID );
	glBindVertexArray( vertexBufferID );
	ExitOnGLError("ERROR: Could not generate the VAO");
  
	// "Bind" them, which means they are ready to be loaded with data
	glGenBuffers(1, &vertexColourBufferID );
	glBindBuffer(GL_ARRAY_BUFFER, vertexColourBufferID);	
	ExitOnGLError("ERROR: Could not bind the VAO");

	// Figure out how big (in "system unit" aka "bytes") the local 
	//	array of vertex information is (i.e. how big is each vertex X number of vertices)
	int bytesInVertexArray = numberOfVerticesLoaded * sizeof(Vertex);

	// This does the actual copy of the date from the "client" (CPU side)
	//	to the GPU ("video card") side. 
	glBufferData(GL_ARRAY_BUFFER, bytesInVertexArray, p_arrayBunnyVertices, GL_STATIC_DRAW);
	ExitOnGLError("ERROR: Could not bind the VBO to the VAO");


	// Now do the same for the index buffer
	glGenBuffers(1, &indexBufferID );			// Get an ID (aka "name")

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferIds[2]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);		
	ExitOnGLError("ERROR: Could not set VAO attributes");

	// Figure out how many "system units" (i.e. "bytes") the index buffer is
	// Or, how many bytes is GLuint (on this system) X number of indices
	int bytesInIndexArray = numberOfIndices * sizeof(GLuint);
	// Copy the data from the CPU RAM to the Video card RAM
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytesInIndexArray, p_bunnyIndices, GL_STATIC_DRAW);
	ExitOnGLError("ERROR: Could not bind the IBO to the VAO");



	glEnableVertexAttribArray(0);			// Position
	glEnableVertexAttribArray(1);			// Colour
	ExitOnGLError("ERROR: Could not enable vertex attributes");

	glVertexAttribPointer(0,		// index or "slot" in the shader
	                      4,		// Number of variables: vec4 would be 4 32-bit variables
						  GL_FLOAT,	// Type: vec4 is float
		                  GL_FALSE, // "normalize" the values (or not)
						  sizeof(Vertex),	// Number of bytes per vertex (the "stride")
						  (GLvoid*)0 );		// Offset from vertex (position is first, so offset = 0
	ExitOnGLError("ERROR: Could not set VAO attributes");

	// http://stackoverflow.com/questions/3718910/can-i-get-the-size-of-a-struct-field-w-o-creating-an-instance-of-the-struct
	int offsetToColourInBytes = sizeof( ((Vertex*)0)->Color );

	glVertexAttribPointer(1, 
	                      4, 
						  GL_FLOAT, 
						  GL_FALSE, 
						  sizeof(Vertex), 
						  (GLvoid*) offsetToColourInBytes );		// Offset in bytes to Colour

	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(VERTICES[0]), (GLvoid*)0);
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VERTICES[0]), (GLvoid*)sizeof(VERTICES[0].Position));
	ExitOnGLError("ERROR: Could not set VAO attributes");


	// Release the "connection" to any vertex buffers
	// Release the binding on all buffers
	glBindVertexArray(0);		
	//glBindBuffer(GL_ARRAY_BUFFER, vertexColourBufferID );
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 

	ExitOnGLError("ERROR: Could not set VAO attributes");


	return true;
}



CModelLoaderManager::CModelLoaderManager()
{
	return;
}

CModelLoaderManager::~CModelLoaderManager()
{
	return;
}




bool CModelLoaderManager::LoadModels( std::vector< std::string > vecFileNames )
{
	// Go through the vector of file names, loading each one, 
	//	then storing the information into the private vector...
	for ( int index = 0; index != vecFileNames.size(); index++ )
	{
		std::string theFileName = vecFileNames[index];

		CPlyInfo tempModelInfo;
		if ( ! this->m_LoadPlyFileIntoGLBuffers( 
										theFileName, tempModelInfo.vertexBufferID, 
										tempModelInfo.vertexColourBufferID, 
										tempModelInfo.indexBufferID, 
										tempModelInfo.numberOfVertices, 
										tempModelInfo.numberOfElements, 
										tempModelInfo.extent ) )
		{	// Something is very wrong... 
			return false;
		}
		// DID work, so:
		// * OpenGL Buffer have been created and are loaded
		// So we will save this information
		tempModelInfo.plyFileASCII = theFileName;	
		this->m_VecModels.push_back( tempModelInfo );
	}

	return true;
}




bool CModelLoaderManager::GetRenderingInfoByModelFileName( std::string modelName, 
		                                                   CPlyInfo &theInfo )
{
	// Search through the vector until we find the model we're looking for
	for ( int index = 0; index != (int)this->m_VecModels.size(); index++ )
	{	// Is this The One?
		if ( this->m_VecModels[index].plyFileASCII == modelName )
		{	// Yup, it is
			theInfo = this->m_VecModels[index];
			return true;
		}
	}
	// Didn't find it.
	return true;
}
