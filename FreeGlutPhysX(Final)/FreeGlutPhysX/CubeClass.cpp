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


#include "CubeClass.h"
#include "Game.h"
#include<cassert>
//void setupFiltering(PxRigidActor* actor, PxU32 filterGroup, PxU32 filterMask)
//{
//	PxFilterData filterData;
//	filterData.word0 = filterGroup; // word0 = own ID
//	filterData.word1 = filterMask;	// word1 = ID mask to filter pairs that trigger a contact callback;
//	const PxU32 numShapes = actor->getNbShapes();
//	PxShape** shapes = (PxShape**)malloc(sizeof(PxShape*)*numShapes);
//	actor->getShapes(shapes, numShapes);
//	for(PxU32 i = 0; i < numShapes; i++)
//	{
//		PxShape* shape = shapes[i];
//		shape->setSimulationFilterData(filterData);
//	}
//	free(shapes);
//}

CCubeClass::CCubeClass(void)
	:m_pActor(0),
	m_fCubeSize(1.f),
	m_Material(0)
{

}


CCubeClass::~CCubeClass(void)
{
	ShutDown();
	

}

void
CCubeClass::ShutDown()
{
	static int debug1 = 0;
	if(m_pActor)
	{
		debug1 += 1;
		m_pActor->release();
		m_pActor = 0;
		//CGame::GetInstance().GetScene()->removeActor(*m_pActor);
	}	

	if(m_Material)
	{
		m_Material->release();
		m_Material = 0;
	}
}

// Author: Scott Emery
// Function: Initialises the cubes. The renderclass has the cubes
// Params: Size of the cube 
// Params: x, y, z holds position variables
bool CCubeClass::Initialise(float _fSize, float _X, float _Y, float _Z)
{
	ShutDown();

	static int debug2 = 0;
	++debug2;
	//if(m_pActor)
	//{
	//	CGame::GetInstance().GetScene()->removeActor(*m_pActor);
	//}

	m_fCubeSize = _fSize;
	
	m_Material = CGame::GetInstance().GetPhysics()->createMaterial(0.5f, 0.5f, 0.1f);

	PxBoxGeometry Geometry(1.0f, 1.0f, 1.0f);

	m_pActor =  PxCreateDynamic(*CGame::GetInstance().GetPhysics(), PxTransform(PxVec3(_X, _Y, _Z)), Geometry,
            *m_Material, 1.0f);

	PxRigidBodyExt::updateMassAndInertia(*m_pActor, 10.0f);

	//setupFiltering(m_pActor, 0, 0);
	
	CGame::GetInstance().GetScene()->addActor(*m_pActor);

	return true;
}

// Author: Scott Emery
// Function: Drawns the cube, also corrects left hand for glut 
//			 when drawing the cubes at location of physx cubes.
// Params: 
void CCubeClass::Draw( float _R, float _G, float _B)
{
	static float sfRotationX = 0;
	glColor3f(_R, _G, _B);

	glPushMatrix();
	PxTransform Pos = m_pActor->getGlobalPose();
	
	PxMat33 Matrix3x3 = PxMat33(Pos.q);

	float fMatrix[16];
	PxMat33 fMatIn = Matrix3x3;
	PxVec3 vec3Transform = Pos.p;
	float* fMatOut = fMatrix;

	glTranslatef(Pos.p.x, Pos.p.y, Pos.p.z);

	fMatOut[0]  = fMatIn.column0[0];
	fMatOut[1]  = fMatIn.column0[1];
	fMatOut[2]  = fMatIn.column0[2];
	fMatOut[3]  = 0;
		    
	fMatOut[4]  = fMatIn.column1[0];
	fMatOut[5]  = fMatIn.column1[1];
	fMatOut[6]  = fMatIn.column1[2];
	fMatOut[7]  = 0;
		    
	fMatOut[8]  = fMatIn.column2[0];
	fMatOut[9]  = fMatIn.column2[1];
	fMatOut[10] = fMatIn.column2[2];
	fMatOut[11] = 0;

	fMatOut[12] = vec3Transform[0];
	fMatOut[13] = vec3Transform[1];
	fMatOut[14] = vec3Transform[2];
	fMatOut[15] = 1;

	glMultMatrixf(fMatrix);

	PxBoxGeometry BoxGeometry(2,2,2);

	glutSolidCube(BoxGeometry.halfExtents.x * 2);

	glPopMatrix();
}

// Author: Scott Emery
// Function: Returns actor for use in render and keyboard
// Params: 
PxRigidDynamic* CCubeClass::GetActor()
{
	return(m_pActor);
}