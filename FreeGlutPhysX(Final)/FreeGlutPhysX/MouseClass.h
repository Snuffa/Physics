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
#include "RenderClass.h"


#pragma once
class CMouseClass
{
public:
	CMouseClass(void);
	~CMouseClass(void);
	void Initialise();
	void UseMouse(int _MouseButton, int _MouseButtonUpOrDown, int _X, int _Y);

private:
	//CCubeClass* m_FireCubes;
	CCubeClass* m_pCube;

};

