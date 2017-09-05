#include "stdafx.h"
#include "Renderer.h"

bool gbShowCollision = false;

#define nop(a, s) _nop((void*)(a), (s))

static void _nop(void* pAddress, DWORD size)
{
		DWORD dwAddress = (DWORD)pAddress;
		if ( size % 2 )
		{
			*(BYTE*)pAddress = 0x90;
			dwAddress++;
		}
		if ( size - ( size % 2 ) )
		{
			DWORD sizeCopy = size - ( size % 2 );
			do
			{
				*(WORD*)dwAddress = 0xFF8B;
				dwAddress += 2;
				sizeCopy -= 2;
			}
			while ( sizeCopy );	
		}
}

#define PATCH_NOTHING	0x00
#define PATCH_CALL		0xE8
#define PATCH_JUMP		0xE9

static void call (DWORD address, void * function, BYTE type) {
	if (type) *(BYTE *)address = type;
	*(DWORD *)++address = (DWORD)function-address-4;	
}

#define patch(a, v, s) _patch((void*)(a), (DWORD)(v), (s))
static void _patch(void* pAddress, DWORD data, DWORD iSize)
{
	memcpy(pAddress, &data, iSize);
}

void patchhh()
{
	CRenderer::RenderFirstPersonVehicle();

	static bool keystate = false;
	if (GetAsyncKeyState(VK_F12) & 0x8000)
	{
		if (!keystate)
		{
			keystate = true;
			gbShowCollision ^= true;
		}
	}
	else keystate = false;

	CRenderer::RenderCollisionLines();
}

inline void UnlockMemOrExit()
{
	DWORD dwValue;
	if (!VirtualProtect((LPVOID)0x401000, 0x857000 - 0x401000, PAGE_EXECUTE_READWRITE, &dwValue) ||
		!VirtualProtect((LPVOID)0x85837C, 0x8A4000 - 0x85837C, PAGE_READWRITE, &dwValue))
	{
		//debug("Virtual Protect error!");
		exit(0);
	}
}

void GENERAL_PATCH()
{
	call(0x53E222, patchhh, PATCH_CALL);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		UnlockMemOrExit();
		GENERAL_PATCH();
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}