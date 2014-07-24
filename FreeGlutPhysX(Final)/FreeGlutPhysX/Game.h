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


#include "RenderClass.h"
#include "KeyBoardClass.h"
#include "MouseClass.h"

#include "PhysXClass.h"


#pragma once
class CGame
{
public:
	static CGame* s_pGame;
	~CGame(void);

	static CGame& GetInstance();
	static void ShutDown();

	bool Initialise();
	void Keys(unsigned char, int, int);
	void Mouse(int, int, int, int);
	void RenderScene();
	void MoveCubes(float);
	PxPhysics* GetPhysics();
	PxScene* GetScene();
	CKeyBoardClass* GetKeyboard();
	CRenderClass* GetRender();

private:
	CGame(void);

	CRenderClass* m_pRender;
	CKeyBoardClass* m_pKeyBoard;
	CMouseClass* m_pMouse;
	CPhysXClass* m_pPhysics;
};

