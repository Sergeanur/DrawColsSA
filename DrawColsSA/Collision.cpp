#include "stdafx.h"
#include "Collisions.h"
#include "Lines.h"

RwBool RwRenderStateSet(int a1, int a2)
{
	int l = *(int*)0xC97B24;
	l += 0x20;
	l = *(int*)l;
	return ((RwBool (__cdecl *)(int, int))l)(a1, a2);

}

void CCollision::LineTest()
{
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, 1);
	RwRenderStateSet(12, 1);
	RwRenderStateSet(10, 5);
	RwRenderStateSet(11, 6);
	RwRenderStateSet(1, 0);

	CLines::RenderLineWithClipping(0, 0, 0, 100, 100, 10.0, 0xFF0000FF, 0xFF0000FF);

	RwRenderStateSet(10, 5);
	RwRenderStateSet(11, 6);
	RwRenderStateSet(12, 0);
	RwRenderStateSet(8, 1);
	RwRenderStateSet(6, 1);
}

void CCollision::DrawColModel(const CMatrix& matrix, const CColModel& colModel)
{
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, true);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, true);
	RwRenderStateSet(rwRENDERSTATESRCBLEND, rwBLENDSRCALPHA);
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, rwBLENDINVSRCALPHA);
	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, NULL);
	auto sup = colModel.m_boundBox.m_vecSup;
	auto inf = colModel.m_boundBox.m_vecInf;

	auto workVec = sup;
	CVector v1 = matrix * workVec;

	workVec.z = inf.z;
	CVector v2 = matrix * workVec;

	workVec = sup;
	workVec.x = inf.x;
	CVector v3 = matrix * workVec;

	workVec = sup;
	workVec.y = inf.y;
	CVector v4 = matrix * workVec;

	workVec = sup;
	workVec.y = inf.y;
	workVec.z = inf.z;
	CVector v5 = matrix * workVec;

	workVec = sup;
	workVec.x = inf.x;
	workVec.z = inf.z;
	CVector v6 = matrix * workVec;

	workVec = sup;
	workVec.x = inf.x;
	workVec.y = inf.y;
	CVector v7 = matrix * workVec;

	workVec = inf;
	CVector v8 = matrix * workVec;

	CLines::RenderLineWithClipping(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, 0xFF0000FF, 0xFF0000FF);
	CLines::RenderLineWithClipping(v1.x, v1.y, v1.z, v3.x, v3.y, v3.z, 0xFF0000FF, 0xFF0000FF);
	CLines::RenderLineWithClipping(v1.x, v1.y, v1.z, v4.x, v4.y, v4.z, 0xFF0000FF, 0xFF0000FF);
	CLines::RenderLineWithClipping(v5.x, v5.y, v5.z, v2.x, v2.y, v2.z, 0xFF0000FF, 0xFF0000FF);
	CLines::RenderLineWithClipping(v5.x, v5.y, v5.z, v8.x, v8.y, v8.z, 0xFF0000FF, 0xFF0000FF);
	CLines::RenderLineWithClipping(v5.x, v5.y, v5.z, v4.x, v4.y, v4.z, 0xFF0000FF, 0xFF0000FF);
	CLines::RenderLineWithClipping(v6.x, v6.y, v6.z, v2.x, v2.y, v2.z, 0xFF0000FF, 0xFF0000FF);
	CLines::RenderLineWithClipping(v6.x, v6.y, v6.z, v8.x, v8.y, v8.z, 0xFF0000FF, 0xFF0000FF);
	CLines::RenderLineWithClipping(v6.x, v6.y, v6.z, v3.x, v3.y, v3.z, 0xFF0000FF, 0xFF0000FF);
	CLines::RenderLineWithClipping(v7.x, v7.y, v7.z, v8.x, v8.y, v8.z, 0xFF0000FF, 0xFF0000FF);
	CLines::RenderLineWithClipping(v7.x, v7.y, v7.z, v3.x, v3.y, v3.z, 0xFF0000FF, 0xFF0000FF);
	CLines::RenderLineWithClipping(v7.x, v7.y, v7.z, v4.x, v4.y, v4.z, 0xFF0000FF, 0xFF0000FF);

	if (colModel.m_pColData)
	{
		for (int i = 0; i < colModel.m_pColData->m_nNumSpheres; i++)
		{
			CVector workVec = matrix * colModel.m_pColData->m_pSpheres[i].m_vecCenter;
			
			CVector v1 = workVec;
			v1.z += colModel.m_pColData->m_pSpheres[i].m_fRadius;

			CVector v2 = workVec;
			v2.z -= colModel.m_pColData->m_pSpheres[i].m_fRadius;

			CVector v3 = workVec;
			v3.x += colModel.m_pColData->m_pSpheres[i].m_fRadius;

			CVector v4 = workVec;
			v4.x -= colModel.m_pColData->m_pSpheres[i].m_fRadius;

			CVector v5 = workVec;
			v5.y += colModel.m_pColData->m_pSpheres[i].m_fRadius;

			CVector v6 = workVec;
			v6.y -= colModel.m_pColData->m_pSpheres[i].m_fRadius;

			CLines::RenderLineWithClipping(v1.x, v1.y, v1.z, v3.x, v3.y, v3.z, 0xFF00FFFF, 0xFF00FFFF);
			CLines::RenderLineWithClipping(v1.x, v1.y, v1.z, v4.x, v4.y, v4.z, 0xFF00FFFF, 0xFF00FFFF);
			CLines::RenderLineWithClipping(v2.x, v2.y, v2.z, v3.x, v3.y, v3.z, 0xFF00FFFF, 0xFF00FFFF);
			CLines::RenderLineWithClipping(v2.x, v2.y, v2.z, v4.x, v4.y, v4.z, 0xFF00FFFF, 0xFF00FFFF);

			CLines::RenderLineWithClipping(v1.x, v1.y, v1.z, v5.x, v5.y, v5.z, 0xFF00FFFF, 0xFF00FFFF);
			CLines::RenderLineWithClipping(v1.x, v1.y, v1.z, v6.x, v6.y, v6.z, 0xFF00FFFF, 0xFF00FFFF);
			CLines::RenderLineWithClipping(v2.x, v2.y, v2.z, v5.x, v5.y, v5.z, 0xFF00FFFF, 0xFF00FFFF);
			CLines::RenderLineWithClipping(v2.x, v2.y, v2.z, v6.x, v6.y, v6.z, 0xFF00FFFF, 0xFF00FFFF);
		}

		for (int i = 0; i < colModel.m_pColData->m_nNumLines; i++)
		{
			CVector v1 = matrix * colModel.m_pColData->m_pLines[i].m_vecStart;
			CVector v2 = matrix * colModel.m_pColData->m_pLines[i].m_vecEnd;
			CLines::RenderLineWithClipping(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, 0xFFFFFF, 0xFFFFFF);
		}

		for (int i = 0; i < colModel.m_pColData->m_nNumBoxes; i++)
		{
			auto sup = colModel.m_pColData->m_pBoxes[i].m_vecSup;
			auto inf = colModel.m_pColData->m_pBoxes[i].m_vecInf;

			auto workVec = sup;
			CVector v1 = matrix * workVec;

			workVec.z = inf.z;
			CVector v2 = matrix * workVec;

			workVec = sup;
			workVec.x = inf.x;
			CVector v3 = matrix * workVec;

			workVec = sup;
			workVec.y = inf.y;
			CVector v4 = matrix * workVec;

			workVec = sup;
			workVec.y = inf.y;
			workVec.z = inf.z;
			CVector v5 = matrix * workVec;

			workVec = sup;
			workVec.x = inf.x;
			workVec.z = inf.z;
			CVector v6 = matrix * workVec;

			workVec = sup;
			workVec.x = inf.x;
			workVec.y = inf.y;
			CVector v7 = matrix * workVec;

			workVec = inf;
			CVector v8 = matrix * workVec;

			CLines::RenderLineWithClipping(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, 0xFFFFFFFF, 0xFFFFFFFF);
			CLines::RenderLineWithClipping(v1.x, v1.y, v1.z, v3.x, v3.y, v3.z, 0xFFFFFFFF, 0xFFFFFFFF);
			CLines::RenderLineWithClipping(v1.x, v1.y, v1.z, v4.x, v4.y, v4.z, 0xFFFFFFFF, 0xFFFFFFFF);
			CLines::RenderLineWithClipping(v5.x, v5.y, v5.z, v2.x, v2.y, v2.z, 0xFFFFFFFF, 0xFFFFFFFF);
			CLines::RenderLineWithClipping(v5.x, v5.y, v5.z, v8.x, v8.y, v8.z, 0xFFFFFFFF, 0xFFFFFFFF);
			CLines::RenderLineWithClipping(v5.x, v5.y, v5.z, v4.x, v4.y, v4.z, 0xFFFFFFFF, 0xFFFFFFFF);
			CLines::RenderLineWithClipping(v6.x, v6.y, v6.z, v2.x, v2.y, v2.z, 0xFFFFFFFF, 0xFFFFFFFF);
			CLines::RenderLineWithClipping(v6.x, v6.y, v6.z, v8.x, v8.y, v8.z, 0xFFFFFFFF, 0xFFFFFFFF);
			CLines::RenderLineWithClipping(v6.x, v6.y, v6.z, v3.x, v3.y, v3.z, 0xFFFFFFFF, 0xFFFFFFFF);
			CLines::RenderLineWithClipping(v7.x, v7.y, v7.z, v8.x, v8.y, v8.z, 0xFFFFFFFF, 0xFFFFFFFF);
			CLines::RenderLineWithClipping(v7.x, v7.y, v7.z, v3.x, v3.y, v3.z, 0xFFFFFFFF, 0xFFFFFFFF);
			CLines::RenderLineWithClipping(v7.x, v7.y, v7.z, v4.x, v4.y, v4.z, 0xFFFFFFFF, 0xFFFFFFFF);
		}


		for (int i = 0; i < colModel.m_pColData->m_nNumTriangles; i++)
		{
			CVector v1, v2, v3;
			colModel.m_pColData->GetTrianglePoint(v1, colModel.m_pColData->m_pTriangles[i].m_nVertA);
			colModel.m_pColData->GetTrianglePoint(v2, colModel.m_pColData->m_pTriangles[i].m_nVertB);
			colModel.m_pColData->GetTrianglePoint(v3, colModel.m_pColData->m_pTriangles[i].m_nVertC);
			
			v1 = matrix * v1;
			v2 = matrix * v2;
			v3 = matrix * v3;

			CLines::RenderLineWithClipping(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, 0xFF00FF, 0xFF00FF);
			CLines::RenderLineWithClipping(v1.x, v1.y, v1.z, v3.x, v3.y, v3.z, 0xFF00FF, 0xFF00FF);
			CLines::RenderLineWithClipping(v2.x, v2.y, v2.z, v3.x, v3.y, v3.z, 0xFF00FF, 0xFF00FF);
		}
	}

	RwRenderStateSet(rwRENDERSTATESRCBLEND, 5);
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, 6);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, false);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, true);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, true);
}

void CCollisionData::GetTrianglePoint(CVector& outVec, int vertId)
{
	((void (__thiscall *)(CCollisionData *, CVector&, int))0x40F5E0)(this, outVec, vertId);
}