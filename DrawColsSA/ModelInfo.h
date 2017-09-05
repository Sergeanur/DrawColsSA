#pragma once

#include "BaseModelInfo.h"

class CModelInfo
{
public:
	static CBaseModelInfo **ms_modelInfoPtrs;
};

CBaseModelInfo **CModelInfo::ms_modelInfoPtrs = (CBaseModelInfo**)0xA9B0C8;