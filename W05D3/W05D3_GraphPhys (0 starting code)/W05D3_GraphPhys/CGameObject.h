#ifndef _CGameObject_HG_
#define _CGameObject_HG_

#include <string>
#include "CVector3f.h"
#include "IMediator.h"		// to allow communication with other objects

class CGameObject
{
public:
	CGameObject();		// Default constructor 
	virtual ~CGameObject();  
	CVector3f position;
	CVector3f rotation;
	CVector3f velocity;
	CVector3f acceleration; 
	float scale; 

	std::string name;			// A helpful name
	std::string plyFileName;	// for rendering
	// ADDED on September 29th, 2014
	CVector3f colour;				// We'll eventually use "material" instead of this (Material is more complex)

	// Only called by the IFactory object
	void setMediator( IMediator* pMediator );

	virtual void Update( float deltaTime );

	// Used by the Mediator to send messages
	virtual void receiveMessage( CMessage theMessage, unsigned int senderID );

	unsigned int getID(void);

protected:
	void m_Init(void);	// Called by the constructor. Set's everything to default state

	// Used to communicate with other objects
	IMediator* m_pMediator;

	// Used to figure out what "state" the object is in
	std::string m_State;

	unsigned int m_ID;	// Unique ID value
	// This will "pick" the "next" ID when object is created
	static unsigned int m_nextID;
};

#endif
