//



#include <GL/glut.h>
#include <GL/GLU.h>
#include <GL/GL.h>
#include "PhysXClass.h"

#pragma once


class CCubeClass
{
public:
	CCubeClass(void);
	~CCubeClass(void);
	bool Initialise(float, float _X, float _Y, float _Z);
	void Draw(float _R, float _G, float _B);
	void Process();
	void ShutDown();
	PxRigidDynamic* GetActor();

private:
	float m_fCubeSize;
	PxRigidDynamic* m_pActor;
	PxMaterial* m_Material;
};

