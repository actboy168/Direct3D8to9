#pragma once

#include "Direct3D8.h"

class CDirect3DVolumeTexture8;

class  CDirect3DVolume8
	: public IDirect3DVolume8
{
public:
	CDirect3DVolume8(IDirect3DVolume9* volume, CDirect3DDevice8* device);
	~CDirect3DVolume8();

private:
	IDirect3DVolume9* pVolume9;
	CDirect3DDevice8* pDevice8;
	CDirect3DVolumeTexture8* pVolumeTexture;

public:
	IDirect3DVolume9* ToNine() const { return (!this) ? nullptr : pVolume9; }
	void SetVolumeTexture(CDirect3DVolumeTexture8* texture) { pVolumeTexture = texture; }


public:
	// IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj);
	STDMETHOD_(ULONG, AddRef)(THIS);
	STDMETHOD_(ULONG, Release)(THIS);

public:
	// IDirect3DVolume8 Methods
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice);
	STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags);
	STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData);
	STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid);
	STDMETHOD(GetContainer)(THIS_ REFIID riid, void** ppContainer);
	STDMETHOD(GetDesc)(THIS_ D3D8VOLUME_DESC *pDesc);
	STDMETHOD(LockBox)(THIS_ D3DLOCKED_BOX * pLockedVolume, CONST D3DBOX* pBox, DWORD Flags);
	STDMETHOD(UnlockBox)(THIS);
};
