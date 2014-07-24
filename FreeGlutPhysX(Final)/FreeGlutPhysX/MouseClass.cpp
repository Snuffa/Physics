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


#include "MouseClass.h"
#include "Game.h"


CMouseClass::CMouseClass(void)
{
}


CMouseClass::~CMouseClass(void)
{
	
}


// Author: Scott Emery
// Function: Initialise mouse
// Params:
void 
CMouseClass::Initialise()
{
	

}


// Author: Scott Emery
// Function: Use mouse keys to apply force to firing cubes. Left for left, right for right cube
// Params: _MouseButton - From glut function in main
// Params: _MouseButtonUpOrDown - glut in main, checks if mouse button is up or down.
// Params: _X, _Y - These make the position of the mouse
void 
CMouseClass::UseMouse(int _MouseButton, int _MouseButtonUpOrDown, int _X, int _Y)
{
	if(_MouseButton == GLUT_LEFT_BUTTON)
	{
		m_pCube = CGame::GetInstance().GetRender()->GetCube(36);
		m_pCube->GetActor()->addForce(PxVec3(20,200,299990));
	}
	else if(_MouseButton == GLUT_RIGHT_BUTTON)
	{
		m_pCube = CGame::GetInstance().GetRender()->GetCube(37);
		m_pCube->GetActor()->addForce(PxVec3(20,200,299990));
	}
}