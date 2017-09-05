#pragma once

#include "Pool.h"
#include "Entity.h"

class CBuilding : public CEntity
{
};

class CPools
{
public:
	static CPool<CBuilding>                                     *&ms_pBuildingPool;
};