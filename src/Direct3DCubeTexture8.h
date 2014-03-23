#pragma once

#include "Direct3D8.h"

class CDirect3DCubeTexture8 
	: public IDirect3DCubeTexture8
{
public:
	CDirect3DCubeTexture8(IDirect3DCubeTexture9* texture, CDirect3DDevice8* device);
	~CDirect3DCubeTexture8();

private:
	IDirect3DCubeTexture9* pCubeTexture9;
	CDirect3DDevice8* pDevice8;

public:
	IDirect3DCubeTexture9* ToNine() const { return (!this) ? nullptr: pCubeTexture9; }

public:
	// IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj);
	STDMETHOD_(ULONG, AddRef)(THIS);
	STDMETHOD_(ULONG, Release)(THIS);

public:
	// IDirect3DCubeTexture8 Methods
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
	STDMETHOD(GetCubeMapSurface)(THIS_ D3DCUBEMAP_FACES FaceType, UINT Level, IDirect3DSurface8** ppCubeMapSurface);
	STDMETHOD(LockRect)(THIS_ D3DCUBEMAP_FACES FaceType, UINT Level, D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags);
	STDMETHOD(UnlockRect)(THIS_ D3DCUBEMAP_FACES FaceType, UINT Level);
	STDMETHOD(AddDirtyRect)(THIS_ D3DCUBEMAP_FACES FaceType, CONST RECT* pDirtyRect);
};
