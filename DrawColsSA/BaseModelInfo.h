#pragma once

#include "Collisions.h"

class CBaseModelInfo
{
public:
	void* vmt;
	unsigned int   m_nKey;
	unsigned short m_nRefCount;
	short          m_nTxdIndex;
	unsigned char  m_nAlpha; // 0 - 255
	unsigned char  m_nNum2dEffects;
    short          m_n2dEffectIndex;
    short          m_nObjectInfoIndex;
	union{
		unsigned short m_wFlags;
		struct{
			/* https://code.google.com/p/mtasa-blue/source/browse/tags/1.3.4/MTA10/game_sa/CModelInfoSA.h */
			unsigned char m_bHasBeenPreRendered : 1; // we use this because we need to apply changes only once
			unsigned char m_bAlphaTransparency: 1;
			unsigned char m_bIsLod: 1;
			unsigned char m_bDontCastShadowsOn: 1;
			unsigned char m_bDontWriteZBuffer: 1;
			unsigned char m_bDrawAdditive: 1;
			unsigned char m_bDrawLast: 1;
			unsigned char m_bDoWeOwnTheColModel: 1;
			union{
				struct{
					unsigned char m_bCarmodIsWheel: 1;
					unsigned char bUnknownFlag9: 1;
					unsigned char bUnknownFlag10: 1;
					unsigned char m_bSwaysInWind: 1;
					unsigned char m_bCollisionWasStreamedWithModel: 1;
					unsigned char m_bDontCollideWithFlyer: 1;
					unsigned char m_bHasComplexHierarchy: 1;
					unsigned char m_bWetRoadReflection: 1;
				};
				struct{
					unsigned char pad0: 2;
					unsigned char m_nCarmodId : 5;
					unsigned char pad1: 1;
				};
			};
			
		};
	};
	CColModel        *m_pColModel;
	float             m_fDrawDistance;
	struct RwObject  *m_pRwObject;
};