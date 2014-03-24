#include "Direct3DVolume8.h"
#include "Direct3DDevice8.h"
#include "Direct3DVolumeTexture8.h"

CDirect3DVolume8::CDirect3DVolume8(IDirect3DVolume9* volume, CDirect3DDevice8* device)
: pVolume9(volume)
, pDevice8(device)
{
}

CDirect3DVolume8::~CDirect3DVolume8()
{
}

HRESULT WINAPI CDirect3DVolume8::QueryInterface(THIS_ REFIID riid, void** ppvObj)
{
	if (riid == IID_IUnknown 
		|| riid == IID_IDirect3DVolume8)
	{
		AddRef();
		*ppvObj = this;
		return D3D_OK;
	}

	*ppvObj = NULL;
	return E_NOINTERFACE;
}

ULONG WINAPI CDirect3DVolume8::AddRef(THIS)
{
	return pVolume9->AddRef();
}

ULONG WINAPI CDirect3DVolume8::Release(THIS)
{
	ComptrGurad<IDirect3DVolume9> gurad(pVolume9);
	ULONG count = pVolume9->Release();
	if (1 == count)
	{
		pDevice8->VolumePool.Destory(pVolume9);
		pVolume9 = NULL;
		delete this;
	}
	return count - 1;
}

STDMETHODIMP CDirect3DVolume8::GetDevice(THIS_ IDirect3DDevice8** ppDevice)
{
	if (pDevice8 == NULL)
		return D3DERR_INVALIDCALL;
	pDevice8->AddRef();
	*ppDevice = pDevice8;
	return D3D_OK;
}

STDMETHODIMP CDirect3DVolume8::SetPrivateData(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags)
{
	return pVolume9->SetPrivateData(refguid, pData, SizeOfData, Flags);
}

STDMETHODIMP CDirect3DVolume8::GetPrivateData(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData)
{
	return pVolume9->GetPrivateData(refguid, pData, pSizeOfData);
}

STDMETHODIMP CDirect3DVolume8::FreePrivateData(THIS_ REFGUID refguid)
{
	return pVolume9->FreePrivateData(refguid);
}

STDMETHODIMP CDirect3DVolume8::GetContainer(THIS_ REFIID riid, void** ppContainer)
{
	if (pVolumeTexture == NULL)
		return D3DERR_INVALIDCALL;
	pVolumeTexture->AddRef();
	*ppContainer = pVolumeTexture;
	return D3D_OK;
}

STDMETHODIMP CDirect3DVolume8::GetDesc(THIS_ D3D8VOLUME_DESC *pDesc)
{
	D3DVOLUME_DESC D3DDesc9;
	HRESULT hr = pVolume9->GetDesc(&D3DDesc9);
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

STDMETHODIMP CDirect3DVolume8::LockBox(THIS_ D3DLOCKED_BOX * pLockedVolume, CONST D3DBOX* pBox, DWORD Flags)
{
	return pVolume9->LockBox(pLockedVolume, pBox, Flags);
}

STDMETHODIMP CDirect3DVolume8::UnlockBox(THIS)
{
	return pVolume9->UnlockBox();
}
