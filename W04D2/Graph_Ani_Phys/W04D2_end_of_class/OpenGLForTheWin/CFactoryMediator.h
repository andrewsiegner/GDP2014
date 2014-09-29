#ifndef _CFactoryMediator_HG_
#define _CFactoryMediator_HG_

// Written by Michael Feeney, Fanshawe College, (c) 2014, mfeeney(at)fanshawec.ca
// For the 'Game Development - Advanced Programming' curriculum:  www.fanshawec.ca/en/GDP1
// It may be distributed under the terms of the MIT License: http://opensource.org/licenses/MIT
// Use this code at your own risk. It is indented only as a learning aid.

#include "IFactory.h"
#include "IMediator.h" 

#include <vector>

class CFactoryMediator : public IFactory, IMediator
{
public:
	CFactoryMediator();
	virtual ~CFactoryMediator();
	
	// *********************************
	// From IFactory:
	virtual unsigned int CreateObjectByType( std::string type ); 
	// Called by the renderer
	virtual void getRenderedObjects(std::vector< CGameObject* > &vecObjectsToRender);
	// This is called by the physics updater
	virtual void getPhysicsObjects(std::vector< CGameObject* > &vecObjectsToUpdate );

	virtual bool UpdateObjectPositionByID( unsigned int ID, CVector3f newPosition );
	virtual bool UpdateObjectScaleByID( unsigned int ID, float newScale );
	virtual bool UpdateObjectVelocityByID( unsigned int ID, CVector3f newVelocity );
	virtual bool UpdateObjectRotationByID( unsigned int ID, CVector3f newRotation );
	virtual bool UpdatePlyFileByID( unsigned int ID, std::string newPlyFileName );
	// *********************************

	// From IMediator:
	// Call this to find objects nearby
	virtual std::vector<unsigned int> GetIDOfNearestObjects( CVector3f &location, float radius );
	// Call this to get location of object
	virtual bool GetPositionByID( unsigned int ID, CVector3f &position );
	// Used for objects to call each other
	virtual bool SendMessageToObject( unsigned int TargetID, unsigned int SenderID, CMessage theMessage );

	// *********************************
private:
	// Contains the objects...
	std::vector< CGameObject* > m_GameObjects;

	// Called internally to locate objects. Returns zero (0) if didn't find anything
	CGameObject* m_findObjectByID(int ID);
};

#endif
