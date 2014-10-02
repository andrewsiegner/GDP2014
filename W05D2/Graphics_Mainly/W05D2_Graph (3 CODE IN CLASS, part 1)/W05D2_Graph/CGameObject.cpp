#include "CGameObject.h"

// Initial value of the first CGameObject ID
// (i.e. the unique IDs of the objects will start at this number)
// Note that using an unsigned int, and assuming that it's 32 bits
//	means that it may potentially wrap around at some point. 
// (but you'd have to create 4 billion objects, first)
static const unsigned int FIRSTGAMEOBJECTID = 1000;
unsigned int CGameObject::m_nextID = FIRSTGAMEOBJECTID;


// Called by the constructors
void CGameObject::m_Init(void)
{
	// Assign ID here
	this->m_ID = this->m_nextID;   
	this->m_nextID++;	// Increment

	this->scale = 1.0f;

	this->name = "no name";
	this->plyFileName = "";

	return;
}

CGameObject::CGameObject()
{
	this->m_Init();

	this->m_pMediator = 0;	

	return;
}

void CGameObject::setMediator( IMediator* pMediator )
{
	// The mediator should only be set at construction, so if something
	//	tries to set it again, we prevent it
	if ( this->m_pMediator == 0 )
	{	// Hasn't been set, so assume creator is calling it
		this->m_pMediator = pMediator;
	}
	return;
}

CGameObject::~CGameObject()
{
	return;
}


void CGameObject::Update( float deltaTime )
{
	// Insert behaviour code in here
	int sexyBreakpoint = 0;

	return;
}

unsigned int CGameObject::getID(void)
{
	return this->m_ID;
}

void CGameObject::receiveMessage( CMessage theMessage, unsigned int senderID )
{
	// Some of the messages we "understand"
	//	vecCommand.push_back( CNameValuePair( "ChangeDirection", "X" ) );
	//	vecCommand.push_back( CNameValuePair( "NewXVel", 0.1f ) );


	// Decode message
	// Note: some of this code is sort of "dangerous" as it just assumes that the 
	//	messages are sent in the correct format. You could do some additional checking
	//	for that (is the message the right lenght, etc.?), but that also takes some
	//	time (and makes the code more involved, too). 
	CNameValuePair firstNVPair;

	if ( theMessage.findNVPairByName( "ChangeDirection", firstNVPair ) )
	{	// It's "Change direction", but which?
		if ( firstNVPair.sValue == "X" )
		{	// 2nd NV pair has velocity
			this->velocity.x = theMessage.vecNVPairs.at(1).fValue;
		}
		if ( firstNVPair.sValue == "Y" )
		{
			this->velocity.y = theMessage.vecNVPairs.at(1).fValue;
		}
		if ( firstNVPair.sValue == "Z" )
		{
			this->velocity.z = theMessage.vecNVPairs.at(1).fValue;
		}
	}
	else if ( theMessage.findNVPairByName( "StopMoving", firstNVPair ) )
	{
		this->velocity = CVector3f(0.0f, 0.0f, 0.0f);
	}

	return;
}