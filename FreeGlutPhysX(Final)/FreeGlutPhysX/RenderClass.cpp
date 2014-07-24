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
#include "Game.h"


CRenderClass::CRenderClass(void)
: m_pKeys(0)
{
}


CRenderClass::~CRenderClass(void)
{
	for(int i = 0; i < 40; ++i)
	{
		m_Cube[i].ShutDown();
	}
}

int iRows = 6;
int iCols = 6;


// Author: Scott Emery
// Function: Initialise Render class
// Params: 0
bool CRenderClass::Initialise()
{

	float fSize = 2.0f;
	float fStartPosX = 1.f;
	float fStartPosY = 1.f;
	float fStartPosZ = 10.f;
	float fIncY = 0.0f;
	for(int i = 0; i < iRows; ++i)
	{
		float fIncX = 0.0f;
		
		for(int j = 0; j < iCols; ++j)
		{
			m_Cube[(i * iRows)+ j].Initialise(fSize,	fStartPosX + j * fSize,
														fStartPosY + i * fSize,
														fStartPosZ);
		}

	}

	// Grumpy bird cubes
	m_Cube[36].Initialise(1.0f, 2, 1, -40);
	m_Cube[37].Initialise(1.0f, 8, 1, -40);

	// Birds
	m_Cube[38].Initialise(1.0f, 10, 13, 10);
	m_Cube[39].Initialise(1.0f, 5, 13, 10);

	return true;

}


// Author: Scott Emery
// Function: RenderScene - Renders scene here, draws here too...zzzzz
// Params: 0
void
CRenderClass::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Do camera stuff
	m_pKeys = CGame::GetInstance().GetKeyboard();
	gluLookAt(m_pKeys->GetXPos(), m_pKeys->GetYPos(), m_pKeys->GetZPos(),
			0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f);

	// Draw the cube colors
	DrawGround(0.0f, 0.5f, 0.0f);	

		for(int i = 0; i < iRows; ++i)
	{
		float fIncX = 0.0f;
		for(int j = 0; j < iCols; ++j)
		{
			m_Cube[(i * iRows)+ j].Draw(0.2f , 0.2f, 0.2f);
		}
	}

	m_Cube[36].Draw(.9f, .9f, .0f);
	m_Cube[37].Draw(.9f, .9f, .0f);
	m_Cube[38].Draw(.0f, .6f, .0f);
	m_Cube[39].Draw(.0f, .6f, .0f);

	if(m_Cube[38].GetActor()->getGlobalPose().p.y <= 3 && m_Cube[39].GetActor()->getGlobalPose().p.y <= 3)
	{
		renderBitmapString(4.0f, 4.0f, -1.0f, GLUT_BITMAP_TIMES_ROMAN_24, "You Win!\nPress 'r' to reset the game.");

	}

	glutSwapBuffers();
}


// Author: Scott Emery
// Function: Draws the ground plane for rendering
// Params:
void 
CRenderClass::DrawGround(float _R, float _G, float _B)
{
	glColor3f(_R, _G, _B);

	glBegin(GL_QUADS);
		glVertex3f(-200.0f, 0.0f, -200.0f);
		glVertex3f(-200.0f, 0.0f,  200.0f);
		glVertex3f( 200.0f, 0.0f,  200.0f);
		glVertex3f( 200.0f, 0.0f, -200.0f);
	glEnd();
}


// Author: Scott Emery
// Function: Returns the cube for using elsewhere, e.g applying force in mouseclass
// Params:
CCubeClass* CRenderClass::GetCube(int _CubeNumber)
{
	return(&m_Cube[_CubeNumber]);
}

//void 
//CRenderClass::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
//{
//	for(PxU32 i=0; i < nbPairs; i++)
//	{
//		const PxContactPair& cp = pairs[i];
//
//		if(cp.events & PxPairFlag::eNOTIFY_THRESHOLD_FORCE_FOUND)
//		{
//			//int i = 5;
//		}
//	}
//}


// Author: Scott Emery
// Function: Prints text to screen. This is used for the win condition of the game.
// Params:
void CRenderClass::renderBitmapString(float _X, float _Y, float _Z, void *_font, char *_pcString)
{
	char *c;
	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos3f(_X, _Y , _Z);
	
	for(c =_pcString; *c != '\0'; c++) 
	{
		glutBitmapCharacter(_font, *c);
	}
}