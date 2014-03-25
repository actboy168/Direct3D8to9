#pragma once

#include "Direct3D8.h"

class CDirect3DSwapChain8
	: public IDirect3DSwapChain8
{
public:
	CDirect3DSwapChain8(IDirect3DSwapChain9* swapchain, CDirect3DDevice8* device);
	~CDirect3DSwapChain8();

private:
	IDirect3DSwapChain9* pSwapChain9;
	CDirect3DDevice8* pDevice8;

public:
	IDirect3DSwapChain9* ToNine() const { return (!this) ? nullptr: pSwapChain9; }

public:
	// IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj);
	STDMETHOD_(ULONG, AddRef)(THIS);
	STDMETHOD_(ULONG, Release)(THIS);

public:
	// IDirect3DSwapChain8 Methods
	STDMETHOD(Present)(THIS_ CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion);
	STDMETHOD(GetBackBuffer)(THIS_ UINT BackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface8** ppBackBuffer);
};
