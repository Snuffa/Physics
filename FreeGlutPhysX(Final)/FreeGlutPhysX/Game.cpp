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


#include "Game.h"
#include "KeyBoardClass.h"

CGame* CGame::s_pGame = 0;

CGame::CGame(void)
: m_pRender(0),
m_pKeyBoard(0),
m_pMouse(0),
m_pPhysics(0)
{
}

CGame& CGame::GetInstance()
{
	if(s_pGame == 0)
	{
		s_pGame = new CGame();
	}
	return(*s_pGame);
}

void 
CGame::ShutDown()
{
	delete s_pGame;
	s_pGame = 0;
}

CGame::~CGame(void)
{
	if(m_pMouse)
	{
		delete m_pMouse;
		m_pMouse = 0;
	}

	if(m_pKeyBoard)
	{
		delete m_pKeyBoard;
		m_pKeyBoard = 0;
	}

	if(m_pRender)
	{
		delete m_pRender;
		m_pRender = 0;
	}
	if(m_pPhysics)
	{
		delete m_pPhysics;
		m_pPhysics = 0;
	}
}

// Author: Scott Emery
// Function: Initialises classes needed
// Params:
bool CGame::Initialise()
{	
	m_pPhysics = new CPhysXClass;
	m_pPhysics->Initialise();

	m_pRender = new CRenderClass;
	m_pRender->Initialise();

	m_pKeyBoard = new CKeyBoardClass;
	m_pKeyBoard->Initialise();

	m_pMouse = new CMouseClass;
	m_pMouse->Initialise();

	return(true);
}

// Author: Scott Emery
// Function: Processes the keyboard class
// Params:
void
CGame::Keys(unsigned char _ucChar, int _iX, int _iY)
{
	m_pKeyBoard->processKeys(_ucChar, _iX, _iY);
}

// Author: Scott Emery
// Function: Processes the mouse class
// Params:
void CGame::Mouse(int _MouseButton, int _MouseButtonUpOrDown, int _X, int _Y)
{
	m_pMouse->UseMouse(_MouseButton, _MouseButtonUpOrDown, _X, _Y); 
}

// Author: Scott Emery
// Function: Calls renders scene and uses deltatick
// Params:
void CGame::RenderScene()
{
	m_pPhysics->Stepper(1.0f/60.0f);
	m_pRender->RenderScene();
}

// Author: Scott Emery
// Function: Returns Physics for use
// Params:
PxPhysics* CGame::GetPhysics()
{
	return(m_pPhysics->GetPhysics());
}

// Author: Scott Emery
// Function: Returns scene for use
// Params:
PxScene* CGame::GetScene()
{
	return(m_pPhysics->GetScene());
}

// Author: Scott Emery
// Function: Returns keyboard for use
// Params:
CKeyBoardClass* CGame::GetKeyboard()
{
	return(m_pKeyBoard);
}

// Author: Scott Emery
// Function: Returns render for use
// Params:
CRenderClass* CGame::GetRender()
{
	return(m_pRender);
}

// Author: Scott Emery
// Function: Allows movement of firing cubes
// Params: Distance to move
void CGame::MoveCubes(float _fDistance)
{
	 PxTransform Pos;
	 Pos = CGame::GetInstance().GetRender()->GetCube(36)->GetActor()->getGlobalPose();
	 Pos.p.x += _fDistance;

	 CGame::GetInstance().GetRender()->GetCube(36)->GetActor()->setGlobalPose(Pos);

	 Pos = CGame::GetInstance().GetRender()->GetCube(37)->GetActor()->getGlobalPose();
	 Pos.p.x += _fDistance;

	 CGame::GetInstance().GetRender()->GetCube(37)->GetActor()->setGlobalPose(Pos);
}