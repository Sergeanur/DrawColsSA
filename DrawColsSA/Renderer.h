#pragma once

#include "Entity.h"

class CRenderer
{
public:
	static int& ms_nNoOfVisibleEntities; // B76844
	static CEntity **&ms_aVisibleEntityPtrs; // B75898

	static int& ms_nNoOfVisibleLods; // B76840
	static CEntity **&ms_aVisibleLodPtrs; // B748F8

	static int& ms_nNoOfVisibleSuperLods; // B76838
	static CEntity **&ms_aVisibleSuperLodPtrs; // B74830

	static int& ms_nNoOfInVisibleEntities; // B7683C
	static CEntity **&ms_aInVisibleEntityPtrs; // B745D8

	static CVector& ms_vecCameraPosition;//B76870;

	static void RenderCollisionLines();
	static void RenderFirstPersonVehicle();
};