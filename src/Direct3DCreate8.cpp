#include "Direct3D8.h"

typedef IDirect3D9* (__stdcall* FnDirect3DCreate9)(UINT);

extern "C"
IDirect3D8* __stdcall Direct3DCreate8(UINT /*sdk_version*/)
{
	HMODULE lib = GetModuleHandleW(L"d3d9.dll");
	if (!lib)
	{
		lib = LoadLibraryW(L"d3d9.dll");
		if (!lib)
		{
			return NULL;
		}
	}

	FnDirect3DCreate9 Direct3DCreate9 = (FnDirect3DCreate9)GetProcAddress(lib, "Direct3DCreate9");
	if (!Direct3DCreate9)
	{
		return NULL;
	}

	IDirect3D9* d3d = Direct3DCreate9(D3D_SDK_VERSION);
	return d3d ? new CDirect3D8(d3d): NULL;
}
