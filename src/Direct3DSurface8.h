#pragma once

#include "Direct3D8.h"

class CDirect3DSurface8
	: public IDirect3DSurface8
{
public:
	CDirect3DSurface8(IDirect3DSurface9* surface, CDirect3DDevice8* device);
	~CDirect3DSurface8();

private:
	IDirect3DSurface9* pSurface9;
	CDirect3DDevice8* pDevice8;

public:
	IDirect3DSurface9* ToNine() const { return (!this) ? nullptr: pSurface9; }

public:
	// IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj);
	STDMETHOD_(ULONG, AddRef)(THIS);
	STDMETHOD_(ULONG, Release)(THIS);

	// IDirect3DSurface8 Methods
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice);
	STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags);
	STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData);
	STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid);
	STDMETHOD(GetContainer)(THIS_ REFIID riid, void** ppContainer);
	STDMETHOD(GetDesc)(THIS_ D3D8SURFACE_DESC *pDesc);
	STDMETHOD(LockRect)(THIS_ D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags);
	STDMETHOD(UnlockRect)(THIS);
};
