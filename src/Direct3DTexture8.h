#pragma once

#include "Direct3D8.h"

class CDirect3DTexture8
	: public IDirect3DTexture8
{
public:
	CDirect3DTexture8(IDirect3DTexture9* texture, CDirect3DDevice8* device);
	~CDirect3DTexture8();

private:
	IDirect3DTexture9* pTexture9;
	CDirect3DDevice8* pDevice8;

public:
	IDirect3DTexture9* ToNine() const { return (!this) ? nullptr: pTexture9; }

public:
	// IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj);
	STDMETHOD_(ULONG, AddRef)(THIS);
	STDMETHOD_(ULONG, Release)(THIS);

public:
	// IDirect3DTexture8 Methods
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice);
	STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags);
	STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData);
	STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid);
	STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew);
	STDMETHOD_(DWORD, GetPriority)(THIS);
	STDMETHOD_(void, PreLoad)(THIS);
	STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS);
	STDMETHOD_(DWORD, SetLOD)(THIS_ DWORD LODNew);
	STDMETHOD_(DWORD, GetLOD)(THIS);
	STDMETHOD_(DWORD, GetLevelCount)(THIS);
	STDMETHOD(GetLevelDesc)(THIS_ UINT Level, D3D8SURFACE_DESC *pDesc);
	STDMETHOD(GetSurfaceLevel)(THIS_ UINT Level, IDirect3DSurface8** ppSurfaceLevel);
	STDMETHOD(LockRect)(THIS_ UINT Level, D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags);
	STDMETHOD(UnlockRect)(THIS_ UINT Level);
	STDMETHOD(AddDirtyRect)(THIS_ CONST RECT* pDirtyRect);
};
