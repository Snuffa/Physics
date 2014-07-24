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


#include <PxPhysicsAPI.h>

using namespace physx;
using namespace pxtask;
using namespace PVD;

#pragma once
class CPhysXClass
{
public:
	CPhysXClass(void);
	~CPhysXClass(void);
	void Initialise();
	void CreateMaterial();
	bool Stepper(float);
	PxPhysics* GetPhysics();
	PxScene* GetScene();

private:
	PxPhysics* m_pPhysics;
	PxFoundation* m_pFoundation;
	PxMaterial* m_pMaterial;
	PxScene* m_pScene;
	PvdConnection* m_pConnection;
	PxDefaultCpuDispatcher* m_pCpuDistpatcher;
	CudaContextManager* m_pCudaContextManager;
	int m_NumThreads;
	float m_fAccumulator;
	float m_fStepSize;

	PxRigidStatic* m_Plane;

};

