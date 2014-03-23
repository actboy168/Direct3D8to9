#pragma once

#include "Direct3D8.h"

class CDirect3DVolumeTexture8
	: public IDirect3DVolumeTexture8
{
public:
	CDirect3DVolumeTexture8(IDirect3DVolumeTexture9* texture, CDirect3DDevice8* device);
	~CDirect3DVolumeTexture8();

private:
	IDirect3DVolumeTexture9* pVolumeTexture9;
	CDirect3DDevice8* pDevice8;

public:
	IDirect3DVolumeTexture9* ToNine() const { return (!this) ? nullptr: pVolumeTexture9; }

public:
	// IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj);
	STDMETHOD_(ULONG, AddRef)(THIS);
	STDMETHOD_(ULONG, Release)(THIS);

public:
	// IDirect3DVolumeTexture8 Methods
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice);
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags);
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData);
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid);
    STDMETHOD_(DWORD,  SetPriority)(THIS_ DWORD PriorityNew);
    STDMETHOD_(DWORD,  GetPriority)(THIS);
    STDMETHOD_(void,  PreLoad)(THIS);
    STDMETHOD_(D3DRESOURCETYPE,  GetType)(THIS);
    STDMETHOD_(DWORD,  SetLOD)(THIS_ DWORD LODNew);
    STDMETHOD_(DWORD,  GetLOD)(THIS);
    STDMETHOD_(DWORD,  GetLevelCount)(THIS);
    STDMETHOD(GetLevelDesc)(THIS_ UINT Level, D3D8VOLUME_DESC *pDesc);
    STDMETHOD(GetVolumeLevel)(THIS_ UINT Level, IDirect3DVolume8** ppVolumeLevel);
    STDMETHOD(LockBox)(THIS_ UINT Level, D3DLOCKED_BOX* pLockedVolume, CONST D3DBOX* pBox, DWORD Flags);
    STDMETHOD(UnlockBox)(THIS_ UINT Level);
    STDMETHOD(AddDirtyBox)(THIS_ CONST D3DBOX* pDirtyBox);
};
