#pragma once

#include "rw\rwcore.h"
#include "rw\rphanim.h"
#include "rw\rpuvanim.h"
#include "rw\rpskin.h"
#include "rw\rpmatfx.h"
#include "rw\skeleton.h"

struct CVector : RwV3d
{
	CVector() {};
	CVector(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	CVector(const RwV3d& vect)
	{
		memcpy(this, &vect, sizeof(RwV3d));
	}
	
	float Magnitude() const;
	float Magnitude2D() const;
    float MagnitudeSquared() const;
    float Magnitude2DSquared() const;
	void Normalise();

	inline operator RwV3d()
	{
		return *(RwV3d*)this;
	}

	friend inline CVector operator+(const CVector& left, const CVector& right)
	{ return CVector(left.x + right.x, left.y + right.y, left.z + right.z); }

    friend inline CVector& operator+=(CVector& left, const CVector& right)
	{
		left = left + right;
		return left;
	}

	friend inline CVector operator-(const CVector& left, const CVector& right)
	{ return CVector(left.x - right.x, left.y - right.y, left.z - right.z); }

	friend inline CVector operator-(const CVector& vec)
	{ return CVector(-vec.x, -vec.y, -vec.z); }

    friend inline CVector& operator-=(CVector& left, const CVector& right)
	{
		left = left - right;
		return left;
	}
	
	friend inline CVector operator*(const CVector& left, const CVector &right)
	{ return CVector(left.x * right.x, left.y * right.y, left.z * right.z); }

	friend inline CVector operator*(const CVector& left, const float &right)
	{ return CVector(left.x * right, left.y * right, left.z * right); }

	friend inline CVector operator*(const float &left, const CVector& right)
	{ return right * left; }

	friend inline CVector operator*=(CVector& left, const float &right)
	{
		left = left * right;
		return left;
	}
	friend inline CVector operator/(const CVector& left, const float &right)
	{ return CVector(left.x / right, left.y / right, left.z / right); }

	friend inline CVector operator/=(CVector& left, const float &right)
	{
		left = left / right;
		return left;
	}

};

class CMatrix {
public:
    // RwV3d-like:
    CVector      right;
    unsigned int flags;
    CVector      up;
    unsigned int pad1;
    CVector      at;
    unsigned int pad2;
    CVector      pos;
    unsigned int pad3;
    
	RwMatrix *m_pAttachMatrix;
	bool m_bOwnsAttachedMatrix; // do we need to delete attaching matrix at detaching

    inline CMatrix() {
        m_pAttachMatrix = nullptr;
        m_bOwnsAttachedMatrix = false;
    }

    //CMatrix(plugin::dummy_func_t) {}
	CMatrix(CMatrix const& matrix);
	CMatrix(RwMatrix *matrix, bool temporary); // like previous + attach
	~CMatrix(); // destructor detaches matrix if attached 
	//void Attach(RwMatrix *matrix, bool temporary);
	//void Detach();
	//void CopyOnlyMatrix(CMatrix const& matrix); // copy base RwMatrix to another matrix
	//void Update(); // update RwMatrix with attaching matrix. This doesn't check if attaching matrix is present, so use it only if you know it is present.
	//               // Using UpdateRW() is more safe since it perform this check.
	//void UpdateRW(); // update RwMatrix with attaching matrix.
	//void UpdateRW(RwMatrix *matrix); // update RwMatrix with this matrix
	//void SetUnity();
	//void ResetOrientation();
	//void SetScale(float scale);
	//void SetScale(float x, float y, float z); // scale on three axes
	//void SetTranslateOnly(float x, float y, float z);
	//void SetTranslate(float x, float y, float z); // like previous + reset orientation
	//void SetRotateXOnly(float angle);
	//void SetRotateYOnly(float angle);
	//void SetRotateZOnly(float angle);
	//void SetRotateX(float angle);
	//void SetRotateY(float angle);
	//void SetRotateZ(float angle);
	//void SetRotate(float x, float y, float z); // set rotate on 3 axes
	//void RotateX(float angle);
	//void RotateY(float angle);
	//void RotateZ(float angle);
	//void Rotate(float x, float y, float z); // rotate on 3 axes
	//void Reorthogonalise();
	//void CopyToRwMatrix(RwMatrix *matrix); // similar to UpdateRW(RwMatrixTag *)
	//void SetRotate(CQuaternion  const& quat);
	//void operator=(CMatrix const& right);
	//void operator+=(CMatrix const& right);
	//void operator*=(CMatrix const& right);
	
	friend const CVector operator*(const CMatrix &a2, const CVector &a3);
};

class CMatrixLink : public CMatrix
{
public:
	class CPlaceable  *m_pOwner;
	class CMatrixLink *m_pPrev;
	class CMatrixLink *m_pNext;

	CMatrixLink();
	~CMatrixLink();
	void Insert(CMatrixLink *matrixLink);
	void Remove();
};

class CSimpleTransform
{
public:
	CVector m_vPosn;
	float m_fHeading;

	void UpdateRwMatrix(RwMatrix *out);
	void Invert(CSimpleTransform const& base);
	void UpdateMatrix(class CMatrix *out);
};

class CBox
{
public:
	CVector m_vecSup;
	CVector m_vecInf;

	void Set(CVector  const& sup, CVector  const& inf);
	// updates box corners, like (if left>right then swap(left, right))
	void Recalc();
};

class CBoundingBox : public CBox
{
public:
    CBoundingBox();

    //CBoundingBox(plugin::dummy_func_t) {}
};

#pragma pack(push, 1)
class CompressedVector
{
public:
	signed __int16 x;
	signed __int16 y;
	signed __int16 z;
};
#pragma pack(pop)

static const CVector CrossProduct(CVector &vec1, CVector &vec2)
{
	return CVector(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x);
}
const float DotProduct(const CVector& first, const CVector& second);