#pragma once

#include "Direct3D8.h"

class CDirect3DBaseTexture8
	: public IDirect3DBaseTexture8
{
public:
	CDirect3DBaseTexture8(IDirect3DBaseTexture9* texture, CDirect3DDevice8* device);
	~CDirect3DBaseTexture8();

private:
	IDirect3DBaseTexture9* pBaseTexture9;
	CDirect3DDevice8* pDevice8;

public:
	IDirect3DBaseTexture9* ToNine() const { return (!this) ? nullptr: pBaseTexture9; }

public:
	// IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj);
	STDMETHOD_(ULONG, AddRef)(THIS);
	STDMETHOD_(ULONG, Release)(THIS);

	// IDirect3DBaseTexture8 Methods
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
};
