#include "stdafx.h"
#include "Lines.h"

void CLines::RenderLineWithClipping(float x1, float y1, float z1, float x2, float y2, float z2, unsigned int c1, unsigned int c2)
{
	((void (__cdecl *)(float, float, float, float, float, float, unsigned int, unsigned int))0x6FF4F0)(x1, y1, z1, x2, y2, z2, c1, c2);
}