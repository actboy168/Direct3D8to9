#include "Direct3DTexture8.h"
#include "Direct3DDevice8.h"
#include "Direct3DSurface8.h"

CDirect3DTexture8::CDirect3DTexture8(IDirect3DTexture9* texture, CDirect3DDevice8* device) 
: pTexture9(texture)
, pDevice8(device)
{
}

CDirect3DTexture8::~CDirect3DTexture8()
{
}

HRESULT WINAPI CDirect3DTexture8::QueryInterface(THIS_ REFIID riid, void** ppvObj)
{
	if (riid == IID_IUnknown
		|| riid == IID_IDirect3DResource8
		|| riid == IID_IDirect3DBaseTexture8 
		|| riid == IID_IDirect3DTexture8)
	{
		AddRef();
		*ppvObj = this;
		return D3D_OK;
	}

	*ppvObj = NULL;
	return E_NOINTERFACE;
}

ULONG WINAPI CDirect3DTexture8::AddRef(THIS)
{
	return pTexture9->AddRef();
}

ULONG WINAPI CDirect3DTexture8::Release(THIS)
{
	ComptrGurad<IDirect3DTexture9> gurad(pTexture9);
	ULONG count = pTexture9->Release();
	if (1 == count)
	{
		pDevice8->TexturePool.Destory(pTexture9);
		pTexture9 = NULL;
		delete this;
	}
	return count - 1;
}

STDMETHODIMP CDirect3DTexture8::GetDevice(THIS_ IDirect3DDevice8** ppDevice)
{
	if (pDevice8 == NULL)
		return D3DERR_INVALIDCALL;
	pDevice8->AddRef();
	*ppDevice = pDevice8;
	return D3D_OK;
}

STDMETHODIMP CDirect3DTexture8::SetPrivateData(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags)
{
	return pTexture9->SetPrivateData(refguid, pData, SizeOfData, Flags);
}

STDMETHODIMP CDirect3DTexture8::GetPrivateData(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData)
{
	return pTexture9->GetPrivateData(refguid, pData, pSizeOfData);
}

STDMETHODIMP CDirect3DTexture8::FreePrivateData(THIS_ REFGUID refguid)
{
	return pTexture9->FreePrivateData(refguid);
}

STDMETHODIMP_(DWORD) CDirect3DTexture8::SetPriority(THIS_ DWORD PriorityNew)
{
	return pTexture9->SetPriority(PriorityNew);
}

STDMETHODIMP_(DWORD) CDirect3DTexture8::GetPriority(THIS)
{
	return pTexture9->GetPriority();
}

STDMETHODIMP_(void) CDirect3DTexture8::PreLoad(THIS)
{
	pTexture9->PreLoad();
}

STDMETHODIMP_(D3DRESOURCETYPE) CDirect3DTexture8::GetType(THIS)
{
	return pTexture9->GetType();
}

STDMETHODIMP_(DWORD) CDirect3DTexture8::SetLOD(THIS_ DWORD LODNew)
{
	return pTexture9->SetLOD(LODNew);
}

STDMETHODIMP_(DWORD) CDirect3DTexture8::GetLOD(THIS)
{
	return pTexture9->GetLOD();
}

STDMETHODIMP_(DWORD) CDirect3DTexture8::GetLevelCount(THIS)
{
	return pTexture9->GetLevelCount();
}

STDMETHODIMP CDirect3DTexture8::GetLevelDesc(THIS_ UINT Level, D3D8SURFACE_DESC *pDesc)
{
	D3DSURFACE_DESC D3DDesc9;
	HRESULT hr = pTexture9->GetLevelDesc(Level, &D3DDesc9);
	if (SUCCEEDED(hr))
	{
		pDesc->Format = D3DDesc9.Format;
		pDesc->Height = D3DDesc9.Height;
		pDesc->MultiSampleType = D3DDesc9.MultiSampleType;
		pDesc->Pool = D3DDesc9.Pool;
		pDesc->Type = D3DDesc9.Type;
		pDesc->Usage = D3DDesc9.Usage;
		pDesc->Width = D3DDesc9.Width;
		pDesc->Size = 0;
	}
	return hr;
}

STDMETHODIMP CDirect3DTexture8::GetSurfaceLevel(THIS_ UINT Level, IDirect3DSurface8** ppSurfaceLevel)
{
	IDirect3DSurface9* pSurfaceLevel9 = NULL;
	HRESULT hr = pTexture9->GetSurfaceLevel(Level, &pSurfaceLevel9);
	if (SUCCEEDED(hr))
	{
		*ppSurfaceLevel = pDevice8->SurfacePool.Create(pSurfaceLevel9, pDevice8);
	}
	return hr;
}

STDMETHODIMP CDirect3DTexture8::LockRect(THIS_ UINT Level, D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags)
{
	return pTexture9->LockRect(Level, pLockedRect, pRect, Flags);
}

STDMETHODIMP CDirect3DTexture8::UnlockRect(THIS_ UINT Level)
{
	return pTexture9->UnlockRect(Level);
}

STDMETHODIMP CDirect3DTexture8::AddDirtyRect(THIS_ CONST RECT* pDirtyRect)
{
	return pTexture9->AddDirtyRect(pDirtyRect);
}
