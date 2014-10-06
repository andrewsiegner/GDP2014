// Written by Michael Feeney, Fanshawe College, (c) 2014, mfeeney(at)fanshawec.ca
// For the 'Game Development - Advanced Programming' curriculum:  www.fanshawec.ca/en/GDP1
// It may be distributed under the terms of the MIT License: http://opensource.org/licenses/MIT
// Use this code at your own risk. It is indented only as a learning aid.

#include "CFactoryMediator.h"

#include <math.h>		// for the sqrt()

// Include specific type here (NOT in the header file)
#include "CBunny.h"
#include "CNinjaTeapot.h" 

const std::string BUNNY_PLY_FILENAME = "ply/bun_zipper_res3_onlyXYZ.ply";
const std::string TEAPOT_PLY_FILENAME = "ply/Utah_Teapot_onlyXYZ.ply";
const std::string SPHERE_PLY_FILENAME = "ply/sphere_UV_onlyXYZ.ply";
const std::string SEAFLOOR2_PLY_FILENAME = "ply/Seafloor2_onlyXYZ.ply";

CFactoryMediator::CFactoryMediator()
{

	return;
}

CFactoryMediator::~CFactoryMediator()
{
	// Delete all the objects
	for ( int index = 0; index != static_cast<int>( this->m_GameObjects.size() ); index++ )
	{
		delete this->m_GameObjects[index];
		this->m_GameObjects[index] = 0;		// Not really needed, but what yolo.
	}

	this->m_GameObjects.clear();	// Bye, bye

	return;
}

// Added, INCOMPLETE
// Params that we can pass:
// name = "Type", sValue = type_to_create	<< this is required
// name = "Position", vec4Value
// name = "Orientation", vec4Value
// name = "Colour", vec4Value
// name = "Scale", fValue
// name = "ModelFile", sValue
// name = "BoundingBox", fValue	(Scale updated to fit max extent into this box)
unsigned int CFactoryMediator::CreateObject( CMessage theCreationParams )
{
	// Get "Type" 

	return 0;
}

// This can only be called internally
// Reutrns 0 if can't find the specific type
CGameObject* CFactoryMediator::m_CreateObjectByType( std::string type, CVector3f initPosition, float initScale )
{
	if ( type == "Bunny" )
	{
		// Note constructor passes itself through the "this" pointer
		CGameObject* pTempObject = new CBunny();		// CGameObject
		pTempObject->setMediator( this );
		pTempObject->plyFileName = BUNNY_PLY_FILENAME;
		pTempObject->scale = initScale;
		pTempObject->position = initPosition;
		return pTempObject;
	}

	else if ( type == "Ninja Teapot" )
	{
		// Note constructor passes itself through the "this" pointer
		CGameObject* pTempObject = new CNinjaTeapot();		// CGameObject
		pTempObject->setMediator( this );
		pTempObject->plyFileName = TEAPOT_PLY_FILENAME;
		pTempObject->scale = initScale;
		pTempObject->position = initPosition;
		return pTempObject;
	}
	else if ( type == "Seafloor 2" )
	{
		// Note constructor passes itself through the "this" pointer
		CGameObject* pTempObject = new CBunny();		// CGameObject
		pTempObject->setMediator( this );
		pTempObject->plyFileName = SEAFLOOR2_PLY_FILENAME;
		pTempObject->scale = initScale;
		pTempObject->position = initPosition;
		return pTempObject;
	}
	else if ( type == "Sphere UV" )
	{
		// Note constructor passes itself through the "this" pointer
		CGameObject* pTempObject = new CBunny();		// CGameObject
		pTempObject->setMediator( this );
		pTempObject->plyFileName = SPHERE_PLY_FILENAME;
		pTempObject->scale = initScale;
		pTempObject->position = initPosition;
		return pTempObject;
	}
	
	// Don't know what type you're asking for, so return 0 (invalid pointer)
	return 0;	
}

unsigned int CFactoryMediator::CreateObjectByType( std::string type, CVector3f initPosition )
{
	return this->CreateObjectByType( type, initPosition, 1.0f );
}

unsigned int CFactoryMediator::CreateObjectByType( std::string type )
{
	return this->CreateObjectByType( type, CVector3f( 0.0f, 0.0f, 0.0f ), 1.0f );
}

// From IFactory: This is the "Factory Method" of the Abstract Factory
unsigned int CFactoryMediator::CreateObjectByType( std::string type, CVector3f initPosition, float initScale )
{
	// Note constructor passes itself through the "this" pointer
	CGameObject* p_TempObject = this->m_CreateObjectByType( type, initPosition, initScale );
	// Created? 
	if ( p_TempObject == 0 ) 
	{ 
		// Don't know what type you're asking for
		return 0;	
	}	

	// Add this new object to the vector of game objects
	this->m_GameObjects.push_back( p_TempObject );
	return p_TempObject->getID();
}

unsigned int CreateObjectByType( std::string type, CVector3f initPosition );
unsigned int CreateObjectByType( std::string type, CVector3f initPosition, float initScale );


bool CFactoryMediator::UpdateObjectPositionByID( unsigned int ID, CVector3f newPosition )
{
	CGameObject* pTheGO = this->m_findObjectByID( ID );
	if ( pTheGO == 0 )
	{
		return false;	// Didn't find it
	}
	// Found it
	pTheGO->position = newPosition;
	return true;
}

bool CFactoryMediator::UpdateObjectRotationByID( unsigned int ID, CVector3f newRotation )
{
	CGameObject* pTheGO = this->m_findObjectByID( ID );
	if ( pTheGO == 0 )
	{
		return false;	// Didn't find it
	}
	// Found it
	pTheGO->rotation = newRotation;
	return true;
}


bool CFactoryMediator::UpdateObjectScaleByID( unsigned int ID, float newScale )
{
	CGameObject* pTheGO = this->m_findObjectByID( ID );
	if ( pTheGO == 0 )
	{
		return false;	// Didn't find it
	}
	// Found it
	pTheGO->scale = newScale;
	return true;
}

bool CFactoryMediator::UpdateObjectVelocityByID( unsigned int ID, CVector3f newVelocity )
{
	CGameObject* pTheGO = this->m_findObjectByID( ID );
	if ( pTheGO == 0 )
	{
		return false;	// Didn't find it
	}
	// Found it
	pTheGO->velocity = newVelocity;
	return true;
}

bool CFactoryMediator::UpdatePlyFileByID( unsigned int ID, std::string newPlyFileName )
{
	CGameObject* pTheGO = this->m_findObjectByID( ID );
	if ( pTheGO == 0 )
	{
		return false;	// Didn't find it
	}
	// Found it
	pTheGO->plyFileName = newPlyFileName;
	return true;
}

// Added on September 29, 2014
bool CFactoryMediator::UpdateColourByID( unsigned int ID, CVector3f newColour )
{
	CGameObject* pTheGO = this->m_findObjectByID( ID );
	if ( pTheGO == 0 )
	{
		return false;	// Didn't find it
	}
	// Found it
	pTheGO->colour = newColour;
	return true;
}

// Few options:
// * Make this function "global" i.e. place in a header file that you include
// * Place this in the specifc classes
// * Add it to the CVector3f (it makes sense and CVector3f is already included)
// * Q-n-D: Rename, yo
float getDistanceBetweenPoints_YOLO( CVector3f point1, CVector3f point2 )
{
	float deltaXsquared = ( point2.x - point1.x ) * ( point2.x - point1.x );  // pow()
	float deltaYsquared = ( point2.y - point1.y ) * ( point2.y - point1.y );
	float deltaZsquared = ( point2.z - point1.z ) * ( point2.z - point1.z );

	// There's a number of square root functions. 
	// You many have to include "math.h" or something else. 
	float distance = sqrt( deltaXsquared + deltaYsquared + deltaZsquared );

	return distance;
}

// From IMediator:
// Call this to find objects nearby
std::vector<unsigned int> CFactoryMediator::GetIDOfNearestObjects( CVector3f &location, float radius )
{
	std::vector<unsigned int> vecFoundObjects;

	// TODO: code to find nearest object to be inserted here
	// Loop through all the objects, checking distance: is it closer than radius
	// If so, add to the vecFoundObjects
	for ( int index = 0; index != (int)this->m_GameObjects.size(); index++ )
	{
		float distance = ::getDistanceBetweenPoints_YOLO( location, 
			                                              this->m_GameObjects[index]->position );
		if ( distance <= radius )
		{	// Yup, it's "close enough"
			vecFoundObjects.push_back( this->m_GameObjects[index]->getID() );
		}
	}

	return vecFoundObjects;
}

// Call this to get location of object
bool CFactoryMediator::GetPositionByID( unsigned int ID, CVector3f &position )
{
	// code to find object by ID, then return location
	CGameObject* pObject = this->m_findObjectByID(ID);
	if ( pObject == 0 )
	{
		return false;	// Didn't find object
	}

	position = pObject->position;

	return true;
}

// Called by the renderer
void CFactoryMediator::getRenderedObjects(std::vector< CGameObject* > &vecObjectsToRender)
{
	// Clear vector
	vecObjectsToRender.clear();

	// Copy all the objects here to external
	for ( int index = 0; index != (int)this->m_GameObjects.size(); index++ )
	{
		vecObjectsToRender.push_back( this->m_GameObjects[index] );
	}

	return;
}

void CFactoryMediator::getPhysicsObjects(std::vector< CGameObject* > &vecObjectsToUpdate )
{
	// Clear vector
	vecObjectsToUpdate.clear();

	// Copy all the objects here to external
	for ( int index = 0; index != static_cast<int>( this->m_GameObjects.size() ); index++ )
	{
		vecObjectsToUpdate.push_back( this->m_GameObjects[index] );
	}

	return;
}


CGameObject* CFactoryMediator::m_findObjectByID(int ID)
{
	for ( int index = 0; index != static_cast<int>( this->m_GameObjects.size() ); index++ )
	{
		// This the one? 
		if ( this->m_GameObjects[index]->getID() == ID )
		{
			return this->m_GameObjects[index];		// Return it
		}
	}
	// Didn't find it, so return 0
	return 0;
}


bool CFactoryMediator::SendMessageToObject( unsigned int TargetID, unsigned int SenderID, CMessage theMessage )
{
	// Find the target
	CGameObject* pTarget = this->m_findObjectByID( TargetID );
	if ( pTarget == 0 )
	{	// Nope, can't find it. 
		return false;
	}

	// We could do other stuff here, too, maybe.
	
	// At this point, the target has been found
	pTarget->receiveMessage( theMessage, SenderID );


	return true;
}
