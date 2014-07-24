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


#pragma once

class CKeyBoardClass
{
public:
	CKeyBoardClass(void);
	~CKeyBoardClass(void);
	void Initialise();
	void processKeys(unsigned char _ucKey, int _iX, int _iY);
	float GetXPos();
	float GetYPos();
	float GetZPos();
	float GetXRotation();
	float GetYRotation();
	float GetAngle();

private:
float m_fPosX;
float m_fPosY;
float m_fPosZ;
float m_fRotX;
float m_fRotY;
float m_fAngle;



};