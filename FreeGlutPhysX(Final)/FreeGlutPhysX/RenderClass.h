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


#include <GL/glut.h>
#include <GL/GLU.h>
#include <GL/GL.h>

#include "CubeClass.h"
#include "KeyBoardClass.h"
#include "PhysXClass.h"

#pragma once
class CRenderClass
{
public:
	CRenderClass(void);
	~CRenderClass(void);

	//virtual void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count)
	//{
	//}
	//virtual void onWake(PxActor** actors, PxU32 count)
	//{
	//}
	//virtual void onSleep(PxActor** actors, PxU32 count)
	//{
	//}
	//virtual void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs);
	//virtual void onTrigger(PxTriggerPair* pairs, PxU32 count)
	//{
	//}

	bool Initialise();
	void RenderScene();
	void DrawGround(float, float, float);
	CCubeClass* GetCube(int _CubeNumber);
	void renderBitmapString(float _X, float _Y, float _Z, void *_font, char *_pcString);

private:
	CCubeClass m_Cube[40];  
	CKeyBoardClass* m_pKeys;
};

