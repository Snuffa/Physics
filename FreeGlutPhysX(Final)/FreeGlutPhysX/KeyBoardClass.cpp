//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// Copyright (c) 2013 Media Design School
//
// Author:	Scott Emery
// Grumpy Birds Project
//


#include "KeyBoardClass.h"
#include "Game.h"
#include <math.h>
#include <gl\freeglut.h>

CKeyBoardClass::CKeyBoardClass(void)
{
}


CKeyBoardClass::~CKeyBoardClass(void)
{
}


// Author: Scott Emery
// Function: Initialises the variables
// Params:
void 
CKeyBoardClass::Initialise()
{
	m_fPosX = 10.0f;
	m_fPosY = 10.0f;
	m_fPosZ = -100.0f;
	m_fRotX = 0.0f;
	m_fRotY = 0.0f;
	m_fAngle = 0.0f;
}


// Author: Scott Emery
// Function: Proccessing the key inputs.
// Params: _ucKey is the type of key passed from glut
void 
CKeyBoardClass::processKeys(unsigned char _ucKey, int _iX, int _iY)
{
	if(_ucKey == 27)
	{
		glutLeaveMainLoop();
		//exit(0);
	}
	if(_ucKey == 'q')
	{
		m_fRotX+=1;
		if(m_fRotX >360)
		{
			m_fRotX -= 360;
		}
	}

	if(m_fRotX = 'z')
	{
		m_fRotX -= 1;
		if(m_fRotX < -360)
		{
			m_fRotX += 360;
		}
	}

	if(_ucKey == 'w')
	{
	float fRotRadX;
	float fRotRadY;

	fRotRadX = (m_fRotX / 180 * 3.141592654f);
	fRotRadY = (m_fRotY / 180 * 3.141592654f);

	m_fPosX +=float(sin(fRotRadY));
	m_fPosZ -=float(cos(fRotRadY));
	m_fPosY -=float(sin(fRotRadX));
	}

	if(_ucKey == 's')
	{
		float fRotRadX;
		float fRotRadY;

		fRotRadX = (m_fRotX / 180 * 3.141592654f);
		fRotRadY = (m_fRotY / 180 * 3.141592654f);

		m_fPosX -=float(sin(fRotRadY));
		m_fPosZ +=float(cos(fRotRadY));
		m_fPosY +=float(sin(fRotRadX));
	}

	if(_ucKey == 'd')
	{
		CGame::GetInstance().MoveCubes(-0.1f);
	}

	if(_ucKey == 'a')
	{
		CGame::GetInstance().MoveCubes(0.1f);
	}

	if(_ucKey == 'r')
	{
		CGame::GetInstance().GetRender()->Initialise();
	}

}


// Author: Scott Emery
// Function: Returns pos
// Params:
float CKeyBoardClass::GetXPos()
{
	return(m_fPosX);
}

// Author: Scott Emery
// Function: Returns pos
// Params:
float CKeyBoardClass::GetYPos()
{
	return(m_fPosY);
}
// Author: Scott Emery
// Function: Returns pos
// Params:
float CKeyBoardClass::GetZPos()
{
	return(m_fPosZ);
}
// Author: Scott Emery
// Function: Returns pos
// Params:
float CKeyBoardClass::GetXRotation()
{
	return(m_fRotX);
}
// Author: Scott Emery
// Function: Returns pos
// Params:
float CKeyBoardClass::GetYRotation()
{
	return(m_fRotY);
}
// Author: Scott Emery
// Function: Returns pos
// Params:
float CKeyBoardClass::GetAngle()
{
	return(m_fAngle);
}