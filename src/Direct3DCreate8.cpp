#include "Direct3D8.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dxguid.lib")

extern "C"
IDirect3D8* __stdcall Direct3DCreate8(UINT /*sdk_version*/)
{
	IDirect3D9* d3d = Direct3DCreate9(D3D_SDK_VERSION);
	return d3d ? new CDirect3D8(d3d) : NULL;
}
