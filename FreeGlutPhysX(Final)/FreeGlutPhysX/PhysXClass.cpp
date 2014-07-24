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


#include "PhysXClass.h"
#include <assert.h>
#include "Game.h"


CPhysXClass::CPhysXClass(void)
:m_pPhysics(0),
m_pFoundation(0),
m_pMaterial(0),
m_pScene(0),
m_pCpuDistpatcher(0),
m_pCudaContextManager(0),
m_pConnection(0),
m_Plane(0)
{
}


CPhysXClass::~CPhysXClass(void)
{	
	if(m_pMaterial)
	{
		m_pMaterial->release();
		m_pMaterial = 0;
	}
	
	if (m_pConnection)
	{
		m_pConnection->release();
		m_pConnection = 0;
	}

	if(m_Plane)
	{
		m_Plane->release();
		m_Plane = 0;
	}

	if(m_pScene)
	{
		m_pScene->release();
		m_pScene = 0;
	}
	if(m_pCpuDistpatcher)
	{
		m_pCpuDistpatcher->release();
		m_pCpuDistpatcher = 0;
	}
	if(m_pCudaContextManager)
	{
		m_pCudaContextManager->release();
		m_pCudaContextManager = 0;
	}


	if(m_pPhysics)
	{
		m_pPhysics->release();
		m_pPhysics = 0;
	}

		if(m_pFoundation)
	{
		m_pFoundation->release();
		m_pFoundation = 0;
	}
}

//PxFilterFlags FilterShader(	
//	PxFilterObjectAttributes attributes0, PxFilterData filterData0, 
//	PxFilterObjectAttributes attributes1, PxFilterData filterData1,
//	PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
//{
//	// let triggers through
//	if(PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
//	{
//		pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
//		return PxFilterFlag::eDEFAULT;
//	}
//	// generate contacts for all that were not filtered above
//	pairFlags = PxPairFlag::eCONTACT_DEFAULT;
//
//	// trigger the contact callback for pairs (A,B) where 
//	// the filtermask of A contains the ID of B and vice versa.
//	//if((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
//		pairFlags |= PxPairFlag::eNOTIFY_THRESHOLD_FORCE_FOUND;
//	
//
//	return PxFilterFlag::eDEFAULT;
//}



// Author: Scott Emery
// Function: Initialises the physX stuff, scene, materials, actors, gravity etc
// Params:
void
CPhysXClass::Initialise()
{
	m_pPhysics = NULL;
	m_NumThreads = 2;
	m_fAccumulator = 0.0f;
	m_fStepSize = 1.0f / 60.0f;

	// Statics
	static PxDefaultErrorCallback gDefaultEfforCallback;
	static PxDefaultAllocator gDefaultAllocatorCallback;

	m_pFoundation = NULL;

	m_pFoundation = PxCreateFoundation(PX_PHYSICS_VERSION,
									  gDefaultAllocatorCallback,
									  gDefaultEfforCallback);

	m_pPhysics = PxCreatePhysics(PX_PHYSICS_VERSION,
								*m_pFoundation,
								PxTolerancesScale());


	// Create Scene
	PxSceneDesc sceneDesc(m_pPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.18f, 0.0f);
	
	if(!sceneDesc.cpuDispatcher)
	{
		m_pCpuDistpatcher = PxDefaultCpuDispatcherCreate(m_NumThreads);
		if(!m_pCpuDistpatcher)
		{
			assert(!L"PxDefaultCpuDispatcherCreate failed!");
		}

		sceneDesc.cpuDispatcher = m_pCpuDistpatcher;
	}


	if(!sceneDesc.filterShader)
	{
		sceneDesc.filterShader = &PxDefaultSimulationFilterShader;
		//sceneDesc.simulationEventCallback = CGame::GetInstance().GetRender();
	}

#ifdef PX_WINDOWS

	if(!sceneDesc.gpuDispatcher && m_pCudaContextManager)
	{
		sceneDesc.gpuDispatcher = m_pCudaContextManager->getGpuDispatcher();
	}
#endif

	m_pScene = m_pPhysics->createScene(sceneDesc);
	if(!m_pScene)
	{
		assert(!L"Create Scene Failed!");
	}

	CreateMaterial();
	// Ground plane
	m_Plane = PxCreatePlane(*m_pPhysics, PxPlane(PxVec3(0, 1, 0), 0), *m_pMaterial);
	m_pScene->addActor(*m_Plane);



	// Visual Debugger
	// check if PvdConnection manager is available on this platform
	if(m_pPhysics->getPvdConnectionManager() == NULL)
    return;

	// setup connection parameters
	const char*     pvd_host_ip = "127.0.0.1";  // IP of the PC which is running PVD
	int             port        = 5425;         // TCP port to connect to, where PVD is listening
	unsigned int    timeout     = 100;          // timeout in milliseconds to wait for PVD to respond,
												// consoles and remote PCs need a higher timeout.
	PxVisualDebuggerConnectionFlags connectionFlags = PxVisualDebuggerExt::getAllConnectionFlags();

	// and now try to connect
	m_pConnection = PxVisualDebuggerExt::createConnection(m_pPhysics->getPvdConnectionManager(),
		pvd_host_ip, port, timeout, connectionFlags);
}



// Author: Scott Emery
// Function: Creates material for PhysX
// Params:
void 
CPhysXClass::CreateMaterial()
{
	m_pMaterial = m_pPhysics->createMaterial(0.5f, 0.5f, 0.5f);
	{
		if(!m_pMaterial)
		{
			assert(!L"Create material failed!");
		}
	}
}


// Author: Scott Emery
// Function: Stepper is essentially the deltatick
// Params: float
bool
CPhysXClass::Stepper(float _dt)
{
	m_fAccumulator += _dt;
	if(m_fAccumulator < m_fStepSize)
	{
		return false;
	}

	m_fAccumulator -= m_fStepSize;

	m_pScene->simulate(m_fStepSize);

	m_pScene->fetchResults(true);

	return true;
}


// Author: Scott Emery
// Function: Returns physics. Called from CGame
// Params:
PxPhysics* CPhysXClass::GetPhysics()
{
	return(m_pPhysics);
}


// Author: Scott Emery
// Function: Returns scene. Called from CGame
// Params:
PxScene* CPhysXClass::GetScene()
{
	return(m_pScene);
}