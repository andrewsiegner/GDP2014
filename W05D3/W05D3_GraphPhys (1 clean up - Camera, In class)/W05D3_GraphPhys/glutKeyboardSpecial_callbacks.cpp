#include "global.h"


void glutKeyboard_callback(unsigned char key, int x, int y)
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
	case 'p': case 'P':
		// View from above "birds eye view"
		::g_pCamera->target = CVector3f( 0.0f, 0.0f, 0.0f );// Origin
		::g_pCamera->eye =  CVector3f( 0.0f, 10.0f, 0.1f ); // NOOOOOOOO!

		break;

	case 'o': case 'O':
		// Follow the play-ah.
		::g_pCamera->Follow( ::g_Player_ID, 0.25f, 2.5f, 2.0f );
		break;		

	case 'w': case 'W':		
		::g_pCamera->eye.x -= 0.1f;// Move the camera "left" (-ve x)
		break;
	case 's': case 'S':
		::g_pCamera->eye.x += 0.1f;		// Right (+ve x)
		break;
	case 'a': case 'A':
		::g_pCamera->eye.z -= 0.1f;		// Forward (-ve z)
		break;
	case 'd': case 'D':
		::g_pCamera->eye.z += 0.1f;		// Back (-ve z)
		break;
	};

	return;
}

void glutSpecialKey_callback( int key, int x, int y )
{
	switch ( key )
	{
	case GLUT_KEY_UP:
		//::g_ourObjects[2].z += 0.1f;		// Away (along z axis)
		// Sending a bunny a command
		{
			CMessage theMessage;
			theMessage.vecNVPairs.push_back( CNameValuePair( "ChangeDirection", "Z" ) );
			theMessage.vecNVPairs.push_back( CNameValuePair( "NewZVel", 0.5f ) );
			::g_pFactoryMediator->SendMessageToObject( g_Player_ID, 0, theMessage );
		}
		break;
	case GLUT_KEY_DOWN:
		//::g_ourObjects[2].z -= 0.1f;		// Towards (along z axis)
		{
			CMessage theMessage;
			theMessage.vecNVPairs.push_back( CNameValuePair( "ChangeDirection", "Z" ) );
			theMessage.vecNVPairs.push_back( CNameValuePair( "NewZVel", -0.5f ) );
			::g_pFactoryMediator->SendMessageToObject( g_Player_ID, 0, theMessage );
		}
		break;
	case GLUT_KEY_LEFT:
		{
			CMessage theMessage;
			theMessage.vecNVPairs.push_back( CNameValuePair( "ChangeDirection", "X" ) );
			theMessage.vecNVPairs.push_back( CNameValuePair( "NewXVel", -0.5f ) );
			::g_pFactoryMediator->SendMessageToObject( g_Player_ID, 0, theMessage );
		}
		break;
	case GLUT_KEY_RIGHT:
		{
			CMessage theMessage;
			theMessage.vecNVPairs.push_back( CNameValuePair( "ChangeDirection", "X" ) );
			theMessage.vecNVPairs.push_back( CNameValuePair( "NewXVel", 0.5f ) );
			::g_pFactoryMediator->SendMessageToObject( g_Player_ID, 0, theMessage );
		}
		break;
	};
	return;
}