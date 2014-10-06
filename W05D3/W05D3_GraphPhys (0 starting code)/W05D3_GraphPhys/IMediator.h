#ifndef _IMediator_HG_
#define _IMediator_HG_

#include "CVector3f.h"
#include "CMessage.h"	
#include <vector>

// Interface ("pure virtual" ---  virtual, also "= 0"
class IMediator		// BUNNIES (game objects) "see" this interface
{
public:
	virtual ~IMediator() {};		// need a destructor on interfaces

	// Call this to find objects nearby
	// Returns an empty (zero size) vector if there's nothing in that sphere
	virtual std::vector<unsigned int> GetIDOfNearestObjects( CVector3f &location, float radius ) = 0;

	// Call this to get location of object
	// Returns false if there's no object with that ID
	virtual bool GetPositionByID( unsigned int ID, CVector3f &position ) = 0;

	// Allows objets to communicate with each other
	// Note that we could also do things like have a special TargetID to do special messages, like:
	// TargetID = 0 --> Send to mediator itself
	// TargetID = WHATEVER --> Send a message to everyone (you could set the identifer ID to start
	//                         at some value other than 1, say 1000 (i.e. the first object to be 
	//                         created woudl have ID = 1000; we've done that here: see CGameObject
	//                         constructor cpp code to see the starting value). Any SenderID below 
	//                         that would indicate a "special" message. 
	virtual bool SendMessageToObject( unsigned int TargetID, unsigned int SenderID, CMessage theMessage ) = 0;

};

#endif
