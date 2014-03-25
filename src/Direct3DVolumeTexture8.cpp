#include "Direct3DVolumeTexture8.h"
#include "Direct3DDevice8.h"
#include "Direct3DVolume8.h"

CDirect3DVolumeTexture8::CDirect3DVolumeTexture8(IDirect3DVolumeTexture9* texture, CDirect3DDevice8* device) 
: pVolumeTexture9(texture)
, pDevice8(device)
{
}

CDirect3DVolumeTexture8::~CDirect3DVolumeTexture8()
{
	pDevice8->VolumeTexturePool.Destory(pVolumeTexture9);
	pVolumeTexture9 = NULL;
}

HRESULT WINAPI CDirect3DVolumeTexture8::QueryInterface(THIS_ REFIID riid, void** ppvObj)
{
	if (riid == IID_IUnknown
		|| riid == IID_IDirect3DResource8
		|| riid == IID_IDirect3DBaseTexture8
		|| riid == IID_IDirect3DVolumeTexture8)
	{
		AddRef();
		*ppvObj = this;
		return D3D_OK;
	}

	*ppvObj = NULL;
	return E_NOINTERFACE;
}

ULONG WINAPI CDirect3DVolumeTexture8::AddRef(THIS)
{
	return pVolumeTexture9->AddRef();
}

ULONG WINAPI CDirect3DVolumeTexture8::Release(THIS)
{
	ComptrGurad<IDirect3DVolumeTexture9> gurad(pVolumeTexture9);
	ULONG count = pVolumeTexture9->Release();
	if (1 == count)
	{
		delete this;
	}
	return count - 1;
}

STDMETHODIMP CDirect3DVolumeTexture8::GetDevice(THIS_ IDirect3DDevice8** ppDevice)
{
	if (pDevice8 == NULL)
		return D3DERR_INVALIDCALL;
	pDevice8->AddRef();
	*ppDevice = pDevice8;
	return D3D_OK;
}

STDMETHODIMP CDirect3DVolumeTexture8::SetPrivateData(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags)
{
	return pVolumeTexture9->SetPrivateData(refguid, pData, SizeOfData, Flags);
}

STDMETHODIMP CDirect3DVolumeTexture8::GetPrivateData(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData)
{
	return pVolumeTexture9->GetPrivateData(refguid, pData, pSizeOfData);
}

STDMETHODIMP CDirect3DVolumeTexture8::FreePrivateData(THIS_ REFGUID refguid)
{
	return pVolumeTexture9->FreePrivateData(refguid);
}

STDMETHODIMP_(DWORD) CDirect3DVolumeTexture8::SetPriority(THIS_ DWORD PriorityNew)
{
	return pVolumeTexture9->SetPriority(PriorityNew);
}

STDMETHODIMP_(DWORD) CDirect3DVolumeTexture8::GetPriority(THIS)
{
	return pVolumeTexture9->GetPriority();
}

STDMETHODIMP_(void) CDirect3DVolumeTexture8::PreLoad(THIS)
{
	pVolumeTexture9->PreLoad();
}

STDMETHODIMP_(D3DRESOURCETYPE) CDirect3DVolumeTexture8::GetType(THIS)
{
	return pVolumeTexture9->GetType();
}

STDMETHODIMP_(DWORD) CDirect3DVolumeTexture8::SetLOD(THIS_ DWORD LODNew)
{
	return pVolumeTexture9->SetLOD(LODNew);
}

STDMETHODIMP_(DWORD) CDirect3DVolumeTexture8::GetLOD(THIS)
{
	return pVolumeTexture9->GetLOD();
}

STDMETHODIMP_(DWORD) CDirect3DVolumeTexture8::GetLevelCount(THIS)
{
	return pVolumeTexture9->GetLevelCount();
}

STDMETHODIMP CDirect3DVolumeTexture8::GetLevelDesc(THIS_ UINT Level, D3D8VOLUME_DESC *pDesc)
{
	D3DVOLUME_DESC D3DDesc9;
	HRESULT hr = pVolumeTexture9->GetLevelDesc(Level, &D3DDesc9);
	if (SUCCEEDED(hr))
	{
		pDesc->Depth = D3DDesc9.Depth;
		pDesc->Format = D3DDesc9.Format;
		pDesc->Height = D3DDesc9.Height;
		pDesc->Pool = D3DDesc9.Pool;
		pDesc->Type = D3DDesc9.Type;
		pDesc->Usage = D3DDesc9.Usage;
		pDesc->Width = D3DDesc9.Width;
		pDesc->Size = 0;
	}
	return hr;
}

STDMETHODIMP CDirect3DVolumeTexture8::GetVolumeLevel(THIS_ UINT Level, IDirect3DVolume8** ppVolumeLevel)
{
	IDirect3DVolume9* pVolumeLevel9 = NULL;
	HRESULT hr = pVolumeTexture9->GetVolumeLevel(Level, &pVolumeLevel9);
	if (SUCCEEDED(hr))
	{
		CDirect3DVolume8* pVolumeLevel8 = pDevice8->VolumePool.Create(pVolumeLevel9, pDevice8);
		pVolumeLevel8->SetVolumeTexture(this);
		*ppVolumeLevel = pVolumeLevel8;

	}
	return hr;
}

STDMETHODIMP CDirect3DVolumeTexture8::LockBox(THIS_ UINT Level, D3DLOCKED_BOX* pLockedVolume, CONST D3DBOX* pBox, DWORD Flags)
{
	return pVolumeTexture9->LockBox(Level, pLockedVolume, pBox, Flags);
}

STDMETHODIMP CDirect3DVolumeTexture8::UnlockBox(THIS_ UINT Level)
{
	return pVolumeTexture9->UnlockBox(Level);
}

STDMETHODIMP CDirect3DVolumeTexture8::AddDirtyBox(THIS_ CONST D3DBOX* pDirtyBox)
{
	return pVolumeTexture9->AddDirtyBox(pDirtyBox);
}
