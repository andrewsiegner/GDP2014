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

void glutSpecialKey_callback( int key, int x, int y )
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