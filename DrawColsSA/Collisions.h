#pragma once

#include "General.h"

class CSphere
{
public:
	CVector m_vecCenter;
	float m_fRadius;

	void Set(float radius, CVector  const& center);
};

class CColSphere : public CSphere
{
public:
	unsigned char m_nMaterial;
	unsigned char m_nFlags;
	unsigned char m_nLighting;
	unsigned char m_nLight;

	void Set(float radius, CVector  const& center, unsigned char material , unsigned char flags, unsigned char lighting);
	bool IntersectRay(CVector  const& rayStart, CVector  const& rayEnd, CVector& intPoint1, CVector& intPoint2);
};

class CColBox : public CBox {
public:
	unsigned char m_nMaterial;
	unsigned char m_nFlags;
	unsigned char m_nLighting;
	unsigned char m_nLight;

	void Set(CVector  const& sup, CVector  const& inf, unsigned char material , unsigned char flags, unsigned char lighting);
	void operator=(CColBox const& right);
};

class CColLine {
public:
	CVector m_vecStart;
	float field_C;
	CVector m_vecEnd;
	float field_1C;

	CColLine(CVector  const& start, CVector  const& end);
	void Set(CVector  const& start, CVector  const& end);
};

class CColDisk {
public:
    CVector m_vecStart;
    float m_fStartRadius;
    unsigned char m_nMaterial;
    unsigned char m_nPiece;
    unsigned char m_nLighting;
private:
    char _pad13;
public:
    CVector m_vecEnd;
    float m_fEndRadius;

    void Set(float startRadius, CVector const& start, CVector const& end, float endRadius, unsigned char material, unsigned char pieceType, unsigned char lighting);
};

class CColTriangle {
public:
	unsigned short m_nVertA; // vertex index in vertices array
	unsigned short m_nVertB; // vertex index in vertices array
	unsigned short m_nVertC; // vertex index in vertices array
	unsigned char m_nMaterial;
	unsigned char m_nLight;
};

class CColTrianglePlane {
public:
	CompressedVector m_normal;
	unsigned short m_nDistance;
	unsigned char m_nOrientation;
	
	void GetNormal(CVector &out);
	void Set(CompressedVector  const* vertices, CColTriangle & triangle);
};

class CCollisionData
{
public:
    unsigned short     m_nNumSpheres;
    unsigned short     m_nNumBoxes;
    unsigned short     m_nNumTriangles;
    unsigned char      m_nNumLines;
    struct {
        unsigned char   bUsesDisks : 1;
        unsigned char   bNotEmpty : 1;
        unsigned char b03 : 1;
        unsigned char   bHasFaceGroups : 1;
        unsigned char   bHasShadow : 1;
    }                  m_nFlags;
    CColSphere        *m_pSpheres;
    CColBox           *m_pBoxes;
    union {
        CColLine      *m_pLines;
        CColDisk      *m_pDisks;
    };
    CompressedVector  *m_pVertices;
    CColTriangle      *m_pTriangles;
    CColTrianglePlane *m_pTrianglePlanes;
    unsigned int       m_nNumShadowTriangles;
    unsigned int       m_nNumShadowVertices;
    CompressedVector  *m_pShadowVertices;
    CColTriangle      *m_pShadowTriangles;

    CCollisionData();
    void RemoveCollisionVolumes();
    void Copy(CCollisionData const& arg0);
    void CalculateTrianglePlanes();
    void GetTrianglePoint(CVector& outVec, int vertId);
    void GetShadTrianglePoint(CVector& outVec, int vertId);
    void RemoveTrianglePlanes();
   // void SetLinkPtr(CLink<CCollisionData*> *link);
    //CLink<CCollisionData*> *GetLinkPtr();
};

class CColModel
{
public:
    CBoundingBox m_boundBox;
	CColSphere m_boundSphere;
    CCollisionData *m_pColData;

    CColModel();
    ~CColModel();
    CColModel& operator=(CColModel const& colModel);

    void MakeMultipleAlloc();
    void AllocateData();
    void AllocateData(int numSpheres, int numBoxes, int numLines, int numVertices, int numTriangles, bool disks);
    void AllocateData(int size);
    void RemoveCollisionVolumes();
    void CalculateTrianglePlanes();
    void RemoveTrianglePlanes();

    static void* operator new(unsigned int size);
    static void operator delete(void* data);
};

class CCollision
{
public:
	static void DrawColModel(const CMatrix& matrix, const CColModel& colModel);
	static void LineTest();
};