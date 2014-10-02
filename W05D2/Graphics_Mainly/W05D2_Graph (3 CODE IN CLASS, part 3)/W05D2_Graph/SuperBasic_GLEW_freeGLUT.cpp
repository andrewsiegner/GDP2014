// Some code originally from : http://openglbook.com/the-book.html 

// Comments are from Michael Feeney (mfeeney(at)fanshawec.ca)

#include "global.h"


//#include "Utils.h"								// Moved to global.h
#define WINDOW_TITLE_PREFIX "Chapter 4"
#include <iostream>		// Added
#include <sstream>		// Added

//#define GLM_FORCE_CXX98    
//#define GLM_FORCE_RADIANS
//#include <glm/glm.hpp>
//#include <glm/vec3.hpp> // glm::vec3
//#include <glm/vec4.hpp> // glm::vec4, glm::ivec4
//#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

// ADDED In class on September 18, 2014
#include <vector>
#include <fstream>

// ADDED in class September 19, 2014
//#include "CGameObject.h"				// Moved to global.h
//#include "CTriangle.h"					// Moved to global.h

// Added in Animation on September 19, 2014
#include "CHRTimer.h"

#include "CFactoryMediator.h"

CHRTimer g_simTimer;

//std::vector< CGameObject > g_ourObjects;		// Moved into the factory
//std::vector< CVertex >   g_vecVertices;			// Moved to global.h and global.cpp
//std::vector< CTriangle > g_vecTriangles;		// Moved to global.h and global.cpp
//int g_numberOfVertices;							// Moved to global.h and global.cpp
//int g_numberOfTriangles;						// Moved to global.h and global.cpp

//void LoadPlyFile(void);			// Moved to LoadPlyFileIntoGLBuffers.cpp
// END OF: Added in class September 18

int CurrentWidth = 1400;
int CurrentHeight = 900;
int WindowHandle = 0;

unsigned FrameCount = 0;

//// We need to know where the variables are inside the shader.
//// These numbers indicate the "slot" (set of 4 floats) location
//// You can think of these like the columns in a database table;
////   imagine that we couldn't use the +name+ of the column, but
////   had to use the column number. 
//GLuint ProjectionMatrixUniformLocation = 0;			// Moved to global.h and global.cpp
//GLuint ViewMatrixUniformLocation = 0;				// Moved to global.h and global.cpp
//GLuint ModelMatrixUniformLocation = 0;				// Moved to global.h and global.cpp
//// The "slot" ID of our colour variable in the shader
//GLuint ObjectColourUniformLocation = 0;				// Moved to global.h and global.cpp
//
//// // Added September 30, 2014
//GLuint slot_LightPosition = 0; //uniform vec4 LightPosition;	// Moved to global.h and global.cpp
//GLuint slot_LightColour = 0;	//uniform vec4 LightColour;		// Moved to global.h and global.cpp
//GLuint slot_attenuation = 0;//uniform float attenuation;		// Moved to global.h and global.cpp
//
//// These buffers are where we are placing the vertex and index information
//// Note that these aren't the actual buffers, but the "names" of the buffers.
//// (in OpenGL, a "name" is always an int, not a string)
//// (The {0} is a simple way to clear static array to all zeros. It's a "C" thing, not OpenGL.)
////GLuint BufferIds[3] = { 0 };
//
//GLuint g_VertexPositionBufferID = 0;		// BufferIds[0]		// Moved to global.h and global.cpp
//GLuint g_VertexColourBufferID = 0;			// BufferIds[1]		// Moved to global.h and global.cpp
//GLuint g_IndexBufferID = 0;					// BufferIds[2]		// Moved to global.h and global.cpp
//
//// Same sort of thing as the "name" of the buffer, but these are the 
//// "names" of the shaders we are loading
//GLuint ShaderIds[3] = { 0 };										// Moved to global.h and global.cpp

// These "Matrix" variables are defined in the Utils file.
// But they are really just an array of floats. Check it out.
//Matrix ProjectionMatrix;
//Matrix ViewMatrix;
//Matrix ModelMatrix;

//glm::mat4 matProjection;								// Moved to global.h and global.cpp
//glm::mat4 matView;									// Moved to global.h and global.cpp
//glm::mat4 matWorld;		// aka "Model" matrix		// Moved to global.h and global.cpp


float CubeRotation = 0;
clock_t LastTime = 0;

// The freeGLUT "callback" function definitions.
void ResizeFunction(int, int);
void RenderFunction(void);
void TimerFunction(int);
void IdleFunction(void);
void DestroyCube(void);
// ADDED in class on September 19, 2014
void keyboardFunctionCallback(unsigned char key, int x, int y);
void specialKeyCallback( int key, int x, int y );

// These are used to init everything
bool InitWindow(int, char*[]);
bool Initialize(int, char*[]);
bool CreateCube(void);
void LoadShaders(void);
void DrawCube(void);


CFactoryMediator* g_pFactoryMediator;

unsigned int g_Player_ID = 0;		// Used to locate the player


int main(int argc, char* argv[])
{
	// ADDED in class September 18, 2014

	//LoadPlyFile();

	Initialize(argc, argv);

	LoadShaders();		// Moved from CreateCube

	int numberOfVerticesLoaded = 0;
	int numberOfTrianglesLoaded = 0;


	// CModelLoaderManager
	g_pModelLoader = new CModelLoaderManager();

	std::vector< std::string > vecModelsToLoad;
	vecModelsToLoad.push_back( "ply/Utah_Teapot_onlyXYZ.ply" );
	vecModelsToLoad.push_back( "ply/bun_zipper_res3_onlyXYZ.ply" );
	vecModelsToLoad.push_back( "ply/Seafloor2_onlyXYZ.ply" );
	vecModelsToLoad.push_back( "ply/sphere_UV_onlyXYZ.ply" );

	if ( ! g_pModelLoader->LoadModels( vecModelsToLoad ) )
	{
		std::cout << "Can't load one or more models. Sorry it didn't work out." << std::endl;
		return -1;
	}

	//float maxExtentBunny = 0.0f;
	//float maxExtentTeaPot = 0.0f;

	//LoadPlyFileIntoGLBuffers( "ply/Utah_Teapot_onlyXYZ.ply",  /*bun_zipper_res3_onlyXYZ.ply*/
	//						  ::g_VertexPositionBufferID[0], 
	//						  ::g_VertexColourBufferID[0],
	//						  ::g_IndexBufferID[0], 
	//						  numberOfVerticesLoaded, 
	//						  numberOfTrianglesLoaded, 
	//						  maxExtentTeaPot );		// By Ref
	//// Save for when we render, later
	//::g_numberOfTriangles[0] = numberOfTrianglesLoaded;
	//

	//LoadPlyFileIntoGLBuffers( "ply/bun_zipper_res3_onlyXYZ.ply",  /*bun_zipper_res3_onlyXYZ.ply*/
	//						  ::g_VertexPositionBufferID[1], 
	//						  ::g_VertexColourBufferID[1],
	//						  ::g_IndexBufferID[1], 
	//						  numberOfVerticesLoaded, 
	//						  numberOfTrianglesLoaded, 
	//						  maxExtentBunny );		// By Ref
	//// Save for when we render, later
	//::g_numberOfTriangles[1] = numberOfTrianglesLoaded;	
	
	
	SetShaderUniformVariables();



	g_pFactoryMediator = new CFactoryMediator();

	// For the student at home, you could add something to the factory so that you 
	// can look up the ply file from the ID....



	// This will be the "player" object, so save the ID
	g_Player_ID = g_pFactoryMediator->CreateObjectByType( "Bunny" );
	g_pFactoryMediator->UpdateObjectRotationByID( g_Player_ID, CVector3f( 0.0f, 0.0f, 0.5f ) );
	g_pFactoryMediator->UpdateColourByID( g_Player_ID, CVector3f( 0.75f, 0.5f, 0.3f ) );
	// All objects should be 2.0x2.0x2.x0
	CPlyInfo tempPlyInfo;
	g_pModelLoader->GetRenderingInfoByModelFileName( "ply/bun_zipper_res3_onlyXYZ.ply", tempPlyInfo );
	g_pFactoryMediator->UpdateObjectScaleByID( g_Player_ID, 1.0f / tempPlyInfo.extent );
	//g_pFactoryMediator->UpdateObjectVelocityByID( g_Player_ID, CVector3f( 0.1f, 0.0f, 0.0f ) );

	// Load up the bunnies (or whatever)
	unsigned int ID = g_pFactoryMediator->CreateObjectByType( "Seafloor 2" );
	g_pFactoryMediator->UpdateObjectPositionByID( ID, CVector3f( 1.0f, 0.0f, 0.0f ) );
	g_pFactoryMediator->UpdateColourByID( ID, CVector3f( 62.0f/255.0f, 176.0f/255.0f, 56.0f/255.0f ) );		// I took the colours from an HTML colour picker
	g_pModelLoader->GetRenderingInfoByModelFileName( "ply/Seafloor2_onlyXYZ.ply", tempPlyInfo );
	g_pFactoryMediator->UpdateObjectScaleByID( ID, 25.0f / tempPlyInfo.extent );
	//g_pFactoryMediator->UpdateObjectVelocityByID( ID, CVector3f( 0.0f, -0.3f, 0.0f ) );

	// Add a command to follow:
	//vec[0].name = "FollowObject"   
	//vec[0].iValue = ID of the object to follow
	//vec[1].fValue = 0.1f  		<-- closest distance
	//vec[2].fValue = 0.1f			<-- speed we'll go
	//CMessage mFollowPlayer;
	//mFollowPlayer.vecNVPairs.push_back( CNameValuePair( "FollowObject", static_cast<int>(g_Player_ID) ) );
	//mFollowPlayer.vecNVPairs.push_back( CNameValuePair( 0.5f ) );   // Closest distance
	//mFollowPlayer.vecNVPairs.push_back( CNameValuePair( 0.1f ) );   // Approach speed
	//g_pFactoryMediator->SendMessageToObject( ID, 0, mFollowPlayer );
	ID = g_pFactoryMediator->CreateObjectByType( "Sphere UV" );
	g_pFactoryMediator->UpdateObjectPositionByID( ID, CVector3f( -1.0f, 0.0, 0.0 ) );
	g_pModelLoader->GetRenderingInfoByModelFileName( "ply/sphere_UV_onlyXYZ.ply", tempPlyInfo );
	g_pFactoryMediator->UpdateObjectScaleByID( ID, 1.0f / tempPlyInfo.extent );
	g_pFactoryMediator->UpdateColourByID( ID, CVector3f( 1.0f, 1.0f, 0.0f ) );		// Yellow
	////g_pFactoryMediator->UpdateObjectVelocityByID( ID, CVector3f( 0.3f, 0.0f, 0.0f ) );
	//// Also want to follow, so send same "command" 
	//g_pFactoryMediator->SendMessageToObject( ID, 0, mFollowPlayer );


	// Adding a "command" to one of the bunnies



	// Added in animation on Sept 19
	g_simTimer.Reset();
	g_simTimer.Start();		// Start "counting"

	glutMainLoop();
  
	exit(EXIT_SUCCESS);
}

bool Initialize(int argc, char* argv[])
{
	GLenum GlewInitResult;

	if (! InitWindow(argc, argv) )
	{
		return false;	// Error
	}	
  
	glewExperimental = GL_TRUE;
	GlewInitResult = glewInit();

	if (GLEW_OK != GlewInitResult) 
	{
		//fprintf(
		//  stderr,
		//  "ERROR: %s\n",
		//  glewGetErrorString(GlewInitResult)
		//);
		std::cout << "ERROR: " << glewGetErrorString(GlewInitResult) << std::endl;
		exit(EXIT_FAILURE);
	}
  
	  //fprintf(
	  //  stdout,
	  //  "INFO: OpenGL Version: %s\n",
	  //  glGetString(GL_VERSION)
	  //);
	std::cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	glGetError();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	ExitOnGLError("ERROR: Could not set OpenGL depth testing options");

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	ExitOnGLError("ERROR: Could not set OpenGL culling options");

	//ModelMatrix = IDENTITY_MATRIX;
	//ProjectionMatrix = IDENTITY_MATRIX;
	//ViewMatrix = IDENTITY_MATRIX;

	// This line is moved into the Render function, because we are doing "lookAt"
	//TranslateMatrix(&ViewMatrix, 0, 0, -2);

	//if ( !CreateCube() ) 
	//{
	//	return false;	// Error
	//}

	return true;
}

bool InitWindow(int argc, char* argv[])
{
	glutInit(&argc, argv);
  
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(
	GLUT_ACTION_ON_WINDOW_CLOSE,
	GLUT_ACTION_GLUTMAINLOOP_RETURNS
	);
  
	glutInitWindowSize(CurrentWidth, CurrentHeight);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);

	if(WindowHandle < 1) 
	{
		fprintf(
			stderr,
			"ERROR: Could not create a new rendering window.\n"
		);
		exit(EXIT_FAILURE);
	}
  
	// Tells GLUT what functions to call... ("callback" functions)
	glutReshapeFunc(ResizeFunction);
	glutDisplayFunc(RenderFunction);
	glutIdleFunc(IdleFunction);
	glutTimerFunc(0, TimerFunction, 0);
	glutCloseFunc(DestroyCube);

	glutKeyboardFunc( keyboardFunctionCallback );
	glutSpecialFunc( specialKeyCallback );

	return true;
}

void specialKeyCallback( int key, int x, int y )
{
	switch ( key )
	{
	case GLUT_KEY_UP:
		//::g_ourObjects[2].z += 0.1f;		// Away (along z axis)
		// Sending a bunny a command
		{
			CMessage theMessage;
			theMessage.vecNVPairs.push_back( CNameValuePair( "ChangeDirection", "Y" ) );
			theMessage.vecNVPairs.push_back( CNameValuePair( "NewYVel", 0.25f ) );
			::g_pFactoryMediator->SendMessageToObject( g_Player_ID, 0, theMessage );
		}
		break;
	case GLUT_KEY_DOWN:
		//::g_ourObjects[2].z -= 0.1f;		// Towards (along z axis)
		{
			CMessage theMessage;
			theMessage.vecNVPairs.push_back( CNameValuePair( "ChangeDirection", "Y" ) );
			theMessage.vecNVPairs.push_back( CNameValuePair( "NewYVel", -0.25f ) );
			::g_pFactoryMediator->SendMessageToObject( g_Player_ID, 0, theMessage );
		}
		break;
	case GLUT_KEY_LEFT:
		{
			CMessage theMessage;
			theMessage.vecNVPairs.push_back( CNameValuePair( "ChangeDirection", "X" ) );
			theMessage.vecNVPairs.push_back( CNameValuePair( "NewXVel", -0.25f ) );
			::g_pFactoryMediator->SendMessageToObject( g_Player_ID, 0, theMessage );
		}
		break;
	case GLUT_KEY_RIGHT:
		{
			CMessage theMessage;
			theMessage.vecNVPairs.push_back( CNameValuePair( "ChangeDirection", "X" ) );
			theMessage.vecNVPairs.push_back( CNameValuePair( "NewXVel", 0.25f ) );
			::g_pFactoryMediator->SendMessageToObject( g_Player_ID, 0, theMessage );
		}
		break;
	};
	return;
}

// Called when a key is pressed
void keyboardFunctionCallback(unsigned char key, int x, int y)
{
	switch( key )
	{
	case ' ':		// Space
		{
			CMessage theMessage;
			theMessage.vecNVPairs.push_back( CNameValuePair( "StopMoving" ) );
			::g_pFactoryMediator->SendMessageToObject( g_Player_ID, 0, theMessage );
		}
		break;
	case 'w': case 'W':
		//::g_ourObjects[2].y += 0.1f;	// Up
		//g_ourObjects[2].velY += 0.01f;
		//g_ourObjects[2].m_State = "GOING_UP";
		break;
	case 's': case 'S':
		//::g_ourObjects[2].y -= 0.1f;	// Down
		//::g_ourObjects[2].velY -= 0.01f;	// Down
		//g_ourObjects[2].m_State = "GOING_DOWN";
		break;
	case 'a': case 'A':
		//::g_ourObjects[2].x -= 0.1f;	// Left
		//::g_ourObjects[2].velX -= 0.01f;	// Left
		//g_ourObjects[2].m_State = "GOING_LEFT";
		break;
	case 'd': case 'D':
		//::g_ourObjects[2].x += 0.1f;	// Right
		//::g_ourObjects[2].velX += 0.01f;	// Right
		//g_ourObjects[2].m_State = "GOING_RIGHT";
		break;
	};

	return;
}

void ResizeFunction(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
	glViewport(0, 0, CurrentWidth, CurrentHeight);
	//ProjectionMatrix =
	//  CreateProjectionMatrix(
	//    60,
	//    (float)CurrentWidth / CurrentHeight,
	//    1.0f,
	//    100.0f
	//  );

	g_matProjection = glm::mat4(1.0f);
	g_matProjection = glm::perspective( glm::radians(45.0f), (float)CurrentWidth / CurrentHeight, 0.1f, 100.f);

	//glUseProgram(g_ShaderIds[0]);
	glUseProgram( g_ShaderProgram_ID );

	//glUniformMatrix4fv(ProjectionMatrixUniformLocation, 1, GL_FALSE, ProjectionMatrix.m);
	glUniformMatrix4fv(g_ProjectionMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(g_matProjection));
	glUseProgram(0);

	return;
}

void RenderFunction(void)
{
	++FrameCount;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawCube();
  
	glutSwapBuffers();

	return;
}

static const float g_MAXIMUM_TIME_STEP = 0.1f;		// 10th of a second or 100ms 

void IdleFunction(void)
{
	// Update the "simulation" at this point.
	// 1. Get elapsed time
	g_simTimer.Stop();
	float deltaTime = ::g_simTimer.GetElapsedSeconds();
	// Is the number TOO big (we're in a break point or something?)
	if ( deltaTime > g_MAXIMUM_TIME_STEP )
	{	// Yup, so clamp it to a new value
		deltaTime = g_MAXIMUM_TIME_STEP;
	}
	g_simTimer.Start();

	std::vector< CGameObject* > vec_pGameObjects;
	g_pFactoryMediator->getPhysicsObjects( vec_pGameObjects );

	for ( int index = 0; index != static_cast<int>( vec_pGameObjects.size() ); index++ )
	{
		vec_pGameObjects[index]->position.x += ( vec_pGameObjects[index]->velocity.x * deltaTime ); 
		vec_pGameObjects[index]->position.y += ( vec_pGameObjects[index]->velocity.y * deltaTime );
		vec_pGameObjects[index]->position.z += ( vec_pGameObjects[index]->velocity.z * deltaTime );
	}

	for ( int index = 0; index != static_cast<int>( vec_pGameObjects.size() ); index++ )
	{
		vec_pGameObjects[index]->Update(deltaTime);
	}


	// Either manipulate the objects here or have objects update.
	// Integrate the new location of the object.
	//for ( int index = 0; index != ::g_ourObjects.size(); index++ )
	//{
	//	// Forward Euler integration.
	//	//float movementThisStepX = g_ourObjects[index].velX * deltaTime;
	//	//g_ourObjects[index].x += movementThisStepX;

	//	// Or this
	//	g_ourObjects[index].x += ( g_ourObjects[index].velX * deltaTime ); 
	//	g_ourObjects[index].y += ( g_ourObjects[index].velY * deltaTime );
	//	g_ourObjects[index].z += ( g_ourObjects[index].velZ * deltaTime );
	//}

	// Call update on all the objects
	//for ( int index = 0; index != ::g_ourObjects.size(); index++ )
	//{
	//	g_ourObjects[index].Update(deltaTime);
	//}

	// Reset the display 
	glutPostRedisplay();
	return;
}

void TimerFunction(int Value)
{
  if (0 != Value) 
  {
    //char* TempString = (char*)
    //  malloc(512 + strlen(WINDOW_TITLE_PREFIX));

    //sprintf(
    //  TempString,
    //  "%s: %d Frames Per Second @ %d x %d",
    //  WINDOW_TITLE_PREFIX,
    //  FrameCount * 4,
    //  CurrentWidth,
    //  CurrentHeight
    //);

	std::stringstream ss;
	ss << WINDOW_TITLE_PREFIX << ": " 
		<< FrameCount * 4 << " Frames Per Second @ "
		<< CurrentWidth << " x "
		<< CurrentHeight;

    glutSetWindowTitle(ss.str().c_str());
    //glutSetWindowTitle(TempString);
    //free(TempString);
  }

  FrameCount = 0;
  glutTimerFunc(250, TimerFunction, 1);

  return;
}

void LoadShaders(void)
{
	//g_ShaderIds[0] = glCreateProgram();
	// A "Shader Program" is a container to hold a "set" of shaders
	// (at least a vertex and a fragment shader, but possibly more)
	g_ShaderProgram_ID = glCreateProgram();	


	ExitOnGLError("ERROR: Could not create the shader program");

	//g_ShaderIds[1] = LoadShader("SimpleShader.fragment.glsl", GL_FRAGMENT_SHADER);
	g_VertexShader_ID = LoadShader("SimpleShader.fragment.glsl", GL_FRAGMENT_SHADER);

	//g_ShaderIds[2] = LoadShader("SimpleShader.vertex.glsl", GL_VERTEX_SHADER);
	g_FragmentShader_ID = LoadShader("SimpleShader.vertex.glsl", GL_VERTEX_SHADER);

	// Now we associate these specific COMPILED shaders to the "program"...
	//glAttachShader(g_ShaderIds[0], g_ShaderIds[1]);
	glAttachShader( g_ShaderProgram_ID, g_VertexShader_ID );
	//glAttachShader(g_ShaderIds[0], g_ShaderIds[2]);
	glAttachShader( g_ShaderProgram_ID, g_FragmentShader_ID );

	// Just like when "building" in C or C++, there is a compile, followed by a link phase...
	// This will take the two compiled shaders and link them to a shader "program".
	// At this point, all the uniform variables will be assigned "slots".
	// (in other words, you can't "find" the uniform variables until you link)

	//glLinkProgram(g_ShaderIds[0]);
	glLinkProgram( g_ShaderProgram_ID );

	ExitOnGLError("ERROR: Could not link the shader program");

  return;
}



//bool CreateCube()
//{
//
//  // I moved this code to LoadShaders()
//  //LoadShaders();
//
//
///*  const Vertex VERTICES[8] =
//  {
//    { { -.5f, -.5f,  .5f, 1 }, { 0, 0, 1, 1 } { n,n,n,1.0}},   // A single vertex
//    { { -.5f,  .5f,  .5f, 1 }, { 1, 0, 0, 1 } },
//    { {  .5f,  .5f,  .5f, 1 }, { 0, 1, 0, 1 } },
//    { {  .5f, -.5f,  .5f, 1 }, { 1, 1, 0, 1 } },
//    { { -.5f, -.5f, -.5f, 1 }, { 1, 1, 1, 1 } },
//    { { -.5f,  .5f, -.5f, 1 }, { 1, 0, 0, 1 } },
//    { {  .5f,  .5f, -.5f, 1 }, { 1, 0, 1, 1 } },
//    { {  .5f, -.5f, -.5f, 1 }, { 0, 0, 1, 1 } }
//  };
//  */
//	//// Create a dynamic array to hold vertices...
//	//Vertex* p_arrayBunnyVertices = new Vertex[g_numberOfVertices];
//	//// Copy the data from the bunny vector to this array
// //for ( int vertIndex = 0; vertIndex != g_numberOfVertices; vertIndex++ )
// //{
// //   p_arrayBunnyVertices[vertIndex].Position[0]  = ::g_vecVertices[vertIndex].x;
//	//p_arrayBunnyVertices[vertIndex].Position[1]  = ::g_vecVertices[vertIndex].y;
//	//p_arrayBunnyVertices[vertIndex].Position[2]  = ::g_vecVertices[vertIndex].z;
//	//p_arrayBunnyVertices[vertIndex].Position[3]  = 1.0f;		// 4th should be 1.0 if not sure
//	//// There is also colour values per vertex
// //	p_arrayBunnyVertices[vertIndex].Color[0] = 1.0f;		// Red
//	//p_arrayBunnyVertices[vertIndex].Color[1] = 1.0f;		// Green
//	//p_arrayBunnyVertices[vertIndex].Color[2] = 1.0f;		// Blue
//	//p_arrayBunnyVertices[vertIndex].Color[3] = 1.0f;		// Alpha
// //}
//
//
////  const GLuint INDICES[36] =
////  {
////    0,2,1,  0,3,2,
////    4,3,0,  4,7,3,
////    4,1,5,  4,0,1,
////    3,6,2,  3,7,6,
////    1,6,5,  1,2,6,
////    7,5,6,  7,4,5
////  };
//
// //// Each triangle has three corners, so we need 3 X number of triangles == number of indices
// // int numberOfIndices = ::g_numberOfTriangles * 3;
// // // **************************** HERE'S WHERE I SCREWED UP, YESTERDAY ********************
// // //GLuint* p_bunnyIndices = new GLuint( numberOfIndices );
// // // **************************************************************************************
// // GLuint* p_bunnyIndices = new GLuint[ numberOfIndices ];
// // //GLuint p_bunnyIndices[3851 * 3];
// // for ( int triIndex = 0; triIndex < g_numberOfTriangles; triIndex++ )	// Step by three
// // {
//	//  CTriangle tempTri = g_vecTriangles[triIndex];
//	//  
//	//  int index1 = (triIndex * 3);
//	//  int index2 = (triIndex * 3) + 1;
//	//  int index3 = (triIndex * 3) + 2;
//
//	//p_bunnyIndices[index1] = (GLuint)tempTri.V1;
//	//p_bunnyIndices[index2] = (GLuint)tempTri.V2;
//	//p_bunnyIndices[index3] = (GLuint)tempTri.V3;
//	////p_bunnyIndices[(triIndex * 3) + 0] = (GLuint)g_vecTriangles[triIndex].V1;
//	////p_bunnyIndices[(triIndex * 3) + 1] = (GLuint)g_vecTriangles[triIndex].V2;
//	////p_bunnyIndices[(triIndex * 3) + 2] = (GLuint)g_vecTriangles[triIndex].V3;
// // }
//
//  ModelMatrixUniformLocation = glGetUniformLocation(ShaderIds[0], "ModelMatrix");
//  ViewMatrixUniformLocation = glGetUniformLocation(ShaderIds[0], "ViewMatrix");
//  ProjectionMatrixUniformLocation = glGetUniformLocation(ShaderIds[0], "ProjectionMatrix");
//  // Added on September 29. 
//  // Ask OpenGL the location of our uniform variable.
//  ObjectColourUniformLocation = glGetUniformLocation( ShaderIds[0], "objectColour" );
//
//  slot_LightPosition = glGetUniformLocation( ShaderIds[0], "LightPosition" );//uniform vec4 LightPosition;
//  slot_LightColour   = glGetUniformLocation( ShaderIds[0], "LightColour" );	 //uniform vec4 LightColour; 
//  slot_attenuation   = glGetUniformLocation( ShaderIds[0], "attenuation" );  //uniform float attenuation;
//  ExitOnGLError("ERROR: Could not get shader uniform locations");
//
// 
//  // GLuint BufferIds[3] = { 0 };
//  //glGenVertexArrays(1, &BufferIds[0]);		// Give me a buffer "name" (aka ID)
//  //glGenVertexArrays(1, &g_VertexPositionBufferID );
//  //ExitOnGLError("ERROR: Could not generate the VAO");
//  //
//  ////glBindVertexArray(BufferIds[0]);
//  //glBindVertexArray( g_VertexPositionBufferID );
//  //ExitOnGLError("ERROR: Could not bind the VAO");
//
//  // There are two "slots" being enabled (see shader)
//  glEnableVertexAttribArray(0);			// Position
//  glEnableVertexAttribArray(1);			// Colour
//  //glEnableVertexAttribArray(2);			// Normal
//  ExitOnGLError("ERROR: Could not enable vertex attributes");
//
//
//  //glGenBuffers(2, &BufferIds[1]);
//  //glGenBuffers(1, &g_VertexColourBufferID );
//  //glGenBuffers(1, &g_IndexBufferID );
//
//  //ExitOnGLError("ERROR: Could not generate the buffer objects");
//
//  ////glBindBuffer(GL_ARRAY_BUFFER, BufferIds[1]);	
//  //glBindBuffer(GL_ARRAY_BUFFER, g_VertexColourBufferID);	
//  // From this point onward, any call to glBufferData will go to this buffer
//  // (think "garden hose aimed at your face")
// 
//  
//  //// Boom - copy the "local" vertex array into the video card (VBO)
//  //int bytesInVertexArray = g_numberOfVertices * sizeof(Vertex);
//
//  //// This does the actual copy of the date from the "client" (CPU side)
//  ////	to the GPU ("video card") side. 
//  //glBufferData(GL_ARRAY_BUFFER, bytesInVertexArray, 
//	 //          p_arrayBunnyVertices, GL_STATIC_DRAW);
//  ////glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);
//  //ExitOnGLError("ERROR: Could not bind the VBO to the VAO");
//
//  // The sizeof is passing the number of bytes of the vertex types 
//  // You could manually calulate this (4 x float) = 4 x 4 bytes = 16 bytes per vertex
//  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
//  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(p_arrayBunnyVertices[0].Color)); 
//  //glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(VERTICES[0]), (GLvoid*)0);
//  //glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VERTICES[0]), (GLvoid*)sizeof(VERTICES[0].Position));
//  ExitOnGLError("ERROR: Could not set VAO attributes");
//
//  ////glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferIds[2]);
//  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IndexBufferID);		
//
//  //int bytesInIndexArray = numberOfIndices * sizeof(GLuint);
//  //glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytesInIndexArray, p_bunnyIndices, GL_STATIC_DRAW);
//  ////glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES), INDICES, GL_STATIC_DRAW);
//  //ExitOnGLError("ERROR: Could not bind the IBO to the VAO");
//
//  //glBindVertexArray(0);		// Release the binding on all buffers
//
//  return true;
//}

void DestroyCube()
{
	// We get rid of all the shaders. 
	//	Note that we do this in (sort of) the reverse order that we created them.
	// (We don't *really* have to do that, but
  glDetachShader( g_ShaderProgram_ID, g_VertexShader_ID );		// glDetachShader(g_ShaderIds[0], g_ShaderIds[1]);
  glDetachShader( g_ShaderProgram_ID, g_FragmentShader_ID );	// glDetachShader(g_ShaderIds[0], g_ShaderIds[2]);

  glDeleteShader( g_VertexShader_ID );		// glDeleteShader(g_ShaderIds[1]);
  glDeleteShader( g_FragmentShader_ID );	// glDeleteShader(g_ShaderIds[2]);

  glDeleteProgram( g_ShaderProgram_ID );	// glDeleteProgram(g_ShaderIds[0]);
  ExitOnGLError("ERROR: Could not destroy the shaders");

  //glDeleteBuffers(2, &g_BufferIds[1]);
  //glDeleteVertexArrays(1, &g_BufferIds[0]);

  glDeleteBuffers( 1, &g_IndexBufferID[0] );
  glDeleteBuffers( 1, &g_VertexColourBufferID[0] );
  glDeleteVertexArrays( 1, &g_VertexPositionBufferID[0] );

  ExitOnGLError("ERROR: Could not destroy the buffer objects");
}

void DrawCube(void)
{
	// *********************************
	float CubeAngle;
	clock_t Now = clock();

	if (LastTime == 0)
	LastTime = Now;

	CubeRotation += 45.0f * ((float)(Now - LastTime) / CLOCKS_PER_SEC);
	CubeAngle = DegreesToRadians(CubeRotation);
	LastTime = Now;

	// *********************************
	glm::mat4 matView(1.0f);
	matView = glm::lookAt( glm::vec3(0.0f, 2.0f, 4.0f),			// Camera (aka "Eye")
							glm::vec3(0.0f, 0.0f, 0.0f),		// At (aka "target")
							glm::vec3(0.0f, 1.0f, 0.0f) );		// Up

	// Get the objects we are to render from the factory
	std::vector< CGameObject* > vec_pRenderedObjects;
	g_pFactoryMediator->getRenderedObjects( vec_pRenderedObjects );

	// For each object in the vector, we'll draw it...
	//for ( int index = 0; index != ::g_ourObjects.size(); index++ )
	//{
	for ( int index = 0; index != static_cast<int>( vec_pRenderedObjects.size() ); index++ )
	{
		SetShaderUniformVariables();


		//ModelMatrix = IDENTITY_MATRIX;		/// aka "World" 
		glm::mat4 matWorld = glm::mat4(1.0f);		// aka "World" matrix


		//RotateAboutY(&ModelMatrix, CubeAngle);
		//RotateAboutX(&ModelMatrix, CubeAngle);
		//TranslateMatrix( &ModelMatrix, -1.0f, 0.0f, 0.0f );
		//ScaleMatrix( &ModelMatrix, 5.0f, 5.0f, 5.0f );


		
		//TranslateMatrix( &ModelMatrix, g_ourObjects[index].x, 
			//			g_ourObjects[index].y, g_ourObjects[index].z );
		float x = vec_pRenderedObjects[index]->position.x;
		float y = vec_pRenderedObjects[index]->position.y;
		float z = vec_pRenderedObjects[index]->position.z;

		matWorld = glm::translate( matWorld, 
			                       glm::vec3( vec_pRenderedObjects[index]->position.x, 
								              vec_pRenderedObjects[index]->position.y, 
											  vec_pRenderedObjects[index]->position.z) );

		//RotateAboutX( &ModelMatrix, g_ourObjects[index].rotX );
		//RotateAboutY( &ModelMatrix, g_ourObjects[index].rotY );
		//RotateAboutZ( &ModelMatrix, g_ourObjects[index].rotZ );
	  
		// **** Moved scale transform to the end, so it wouldn't impact the Translate transform ****
		// (Last transform done is the *first* performed mathematically, so put scale at end... or never scale)
		//ScaleMatrix( &ModelMatrix, g_ourObjects[index].scale, 
			//			g_ourObjects[index].scale, g_ourObjects[index].scale );
		


		float scaleTemp = vec_pRenderedObjects[index]->scale;
//
////maxExtent = 134.562973  [0]
////maxExtent = 0.155298904 [1]
//		scaleTemp = 1.0f / 0.155298904;
		matWorld = glm::scale( matWorld, glm::vec3(scaleTemp) );

		// *** START of DRAW THE OBJECT FROM THE BUFFER ****
		// Add this line
		//glPolygonMode( GL_FRONT,  GL_LINE );
		glPolygonMode( GL_FRONT_AND_BACK ,  GL_LINE );
		//glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

		//glUseProgram(g_ShaderIds[0]);
		glUseProgram( g_ShaderProgram_ID );
		ExitOnGLError("ERROR: Could not use the shader program");

		//glUniformMatrix4fv(ModelMatrixUniformLocation, 1, GL_FALSE, ModelMatrix.m);
		//glUniformMatrix4fv(ViewMatrixUniformLocation, 1, GL_FALSE, ViewMatrix.m);
		glUniformMatrix4fv( g_ModelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(matWorld) );
		glUniformMatrix4fv( g_ViewMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(matView) );

		// Add: setting our colour value we just added
		//glm::vec4 colour;
		//colour.a = 1.0f;	colour.g = 0.5f;	colour.b = 0.3f;	
		//glUniform4f( ObjectColourUniformLocation, colour.r, colour.g, colour.b, 1.0f );

		// Take the colour from the object
		glUniform4f( g_ObjectColourUniformLocation, vec_pRenderedObjects[index]->colour.x, 
			                                        vec_pRenderedObjects[index]->colour.y, 
												    vec_pRenderedObjects[index]->colour.z, 1.0f );	// Colour has 4 components (vec4)

		//glUniform4f( ObjectColourUniformLocation, 0.0f, 0.0f, 0.0f, 1.0f );	// BLACK

		// Light position
		glUniform4f( g_slot_LightPosition, 1.0f, 1.0f, 0.0f, 1.0f );	
		// White light
		glUniform4f( g_slot_LightColour, 1.0f, 1.0f, 1.0f, 1.0f );

		float atten = 1.0f / 25.0f;	//
		glUniform1f( g_slot_attenuation, atten	);				


		ExitOnGLError("ERROR: Could not set the shader uniforms");

		//glBindVertexArray(BufferIds[0]);	

		// Based on the object "ply file" name, point to the appropriate buffer

		int numberOfIndicesToRender = 0;
		//if ( vec_pRenderedObjects[index]->plyFileName == "bun_zipper_res3.ply" )
		//{
		//	glBindVertexArray( g_VertexPositionBufferID[1] );				// "Connects" to a vertex buffer
		//	glBindBuffer( GL_ARRAY_BUFFER, g_VertexColourBufferID[1] );		// Also buffer (with colours)
		//	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, g_IndexBufferID[1] );	// And Index buffer	
		//	numberOfIndicesToRender = g_numberOfTriangles[1] * 3; 
		//}
		//else if ( vec_pRenderedObjects[index]->plyFileName == "Utah_Teapot.ply" )
		//{
		//	glBindVertexArray( g_VertexPositionBufferID[0] );				// "Connects" to a vertex buffer
		//	glBindBuffer( GL_ARRAY_BUFFER, g_VertexColourBufferID[0] );		// Also buffer (with colours)
		//	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, g_IndexBufferID[0] );	// And Index buffer	
		//	numberOfIndicesToRender = g_numberOfTriangles[0] * 3; 
		//}
		CPlyInfo tempPlyInfo;
		std::string plyFileNameDEBUG = vec_pRenderedObjects[index]->plyFileName;
		if ( !::g_pModelLoader->GetRenderingInfoByModelFileName( vec_pRenderedObjects[index]->plyFileName, 
			                                                     tempPlyInfo ) )
		{	// Model isn't present, which is a Very Bad Thing
			continue;	// in a for loop, this will go to the next count, skipping everyint
		}
		// At this point, we have found a valid model (that was loaded)
		glBindVertexArray( tempPlyInfo.vertexBufferID );					//  g_VertexPositionBufferID[1] );				// "Connects" to a vertex buffer
		glBindBuffer( GL_ARRAY_BUFFER, tempPlyInfo.vertexColourBufferID );	//  g_VertexColourBufferID[1] );		// Also buffer (with colours)
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, tempPlyInfo.indexBufferID );	// g_IndexBufferID[1] );	// And Index buffer	
		numberOfIndicesToRender = tempPlyInfo.numberOfElements * 3;			// g_numberOfTriangles[1] * 3; 
		

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


		//int numberOfIndicesToRender = g_numberOfTriangles[1] * 3; 
		glDrawElements(GL_TRIANGLES,  
			           numberOfIndicesToRender, 
					   GL_UNSIGNED_INT, (GLvoid*)0 );
		ExitOnGLError("ERROR: Could not draw the cube");
		// *** END of DRAW THE OBJECT FROM THE BUFFER ****

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

	}// for ( int index = 0...

	glBindVertexArray(0);
	glUseProgram(0);

	return;
}

// *** Moved to LoadPlyFileIntoGLBuffers.cpp ***
//void LoadPlyFile(void)
//{
//	std::wifstream myFile("ply/bun_zipper_res3.ply");
//	//std::wifstream myFile("Utah_Teapot.ply");
//	if ( ! myFile.is_open() )		
//		return;
//
//	// Read everything up to the word "vertex"
//	std::wstring temp;
//	bool bKeepReading = true;
//	while ( bKeepReading )
//	{
//		myFile >> temp;				// Read next "string" into temp
//		if ( temp == L"vertex" )	
//		{
//			bKeepReading = false;
//		}
//	};
//	// Next value is number of vertices
//	myFile >> g_numberOfVertices;
//
//	// Same thing, but number of triangles (aka "elements")
//	bKeepReading = true;
//	while ( bKeepReading )
//	{
//		myFile >> temp;
//		if ( temp == L"face" )	
//		{
//			bKeepReading = false;
//		}
//	};
//	// Next value is number of vertices
//	myFile >> g_numberOfTriangles;
//
//	// Same thing, but look for 
//	bKeepReading = true;
//	while ( bKeepReading )
//	{
//		myFile >> temp;
//		if ( temp == L"end_header" )	
//		{
//			bKeepReading = false;
//		}
//	};
//
//	// Now, I can read the actual information... 
//	for ( int count = 0; count != g_numberOfVertices; count++ )
//	{
//		CVertex tempVert;
//		myFile >> tempVert.x >> tempVert.y >> tempVert.z;
//		// Extra two numbers. Read and discard;
//		float temp;
//		myFile >> temp >> temp;
//
//		g_vecVertices.push_back( tempVert );
//	}
//
//	// 
//	for ( int count = 0; count != g_numberOfTriangles; count++ )
//	{
//		CTriangle tempTri;
//		int discard;
//		// 3 564 612 611 
//		myFile >> discard >> tempTri.V1 >> tempTri.V2 >> tempTri.V3;
//
//		g_vecTriangles.push_back( tempTri );
//	}
//
//	myFile.close();  // It's nice to be nice. Close the file.
//
//	return;
//}
