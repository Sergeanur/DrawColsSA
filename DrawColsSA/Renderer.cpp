#include "stdafx.h"
#include "Renderer.h"
#include "ModelInfo.h"
#include "Lines.h"
#include "Collisions.h"
#include "Pools.h"

CPool<CBuilding> *&CPools::ms_pBuildingPool = *(CPool<CBuilding> **)0xB74498;

int& CRenderer::ms_nNoOfVisibleEntities = *(int*)0xB76844;
CEntity **& CRenderer::ms_aVisibleEntityPtrs = *(CEntity ***)0x553944;

int& CRenderer::ms_nNoOfVisibleLods = *(int*)0xB76840;
CEntity **& CRenderer::ms_aVisibleLodPtrs = *(CEntity ***)0x5534F5;

int& CRenderer::ms_nNoOfVisibleSuperLods = *(int*)0xB76838;
CEntity **& CRenderer::ms_aVisibleSuperLodPtrs = *(CEntity ***)0x553965;

int& CRenderer::ms_nNoOfInVisibleEntities = *(int*)0xB7683C;
CEntity **& CRenderer::ms_aInVisibleEntityPtrs = *(CEntity ***)0x553986;

CVector& CRenderer::ms_vecCameraPosition = *(CVector*)0xB76870;

void CRenderer::RenderCollisionLines()
{
	if (gbShowCollision)
	{
		for (int i = 0; i < ms_nNoOfVisibleEntities; i++)
		{
			if (!ms_aVisibleEntityPtrs[i]) continue;
			CMatrix* matrix = ms_aVisibleEntityPtrs[i]->GetMatrix();

			if (!matrix) continue;
			auto index = ms_aVisibleEntityPtrs[i]->m_wModelIndex;
			if (!CModelInfo::ms_modelInfoPtrs[index]) continue;
			auto pColModel = CModelInfo::ms_modelInfoPtrs[index]->m_pColModel;
			if (!pColModel) continue;

			CCollision::DrawColModel(*matrix, *pColModel);
		}
	}
}

void CRenderer::RenderFirstPersonVehicle()
{
	((void (__cdecl *)())0x553D00)();
}