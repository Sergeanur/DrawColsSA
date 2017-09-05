#include "stdafx.h"
#include "General.h"
#include "Placeable.h"

CMatrixLink *CPlaceable::GetMatrix()
{
    return ((CMatrixLink *(__thiscall *)(CPlaceable *))0x411990)(this);
}


const CVector operator*(const CMatrix &m, const CVector &v)
{
	return m.right * v.x + m.up * v.y + m.at * v.z + m.pos;
}

float CVector::MagnitudeSquared() const
{
    return x * x + y * y + z * z;
}

float CVector::Magnitude2DSquared() const
{
    return x * x + y * y;
}

float CVector::Magnitude() const
{
    return sqrt(MagnitudeSquared());
}

const float DotProduct(const CVector& first, const CVector& second)
{
    return first.x * second.x + first.y * second.y + first.z * second.z;
}