#include "Direct3DCubeTexture8.h"
#include "Direct3DDevice8.h"
#include "Direct3DSurface8.h"

CDirect3DCubeTexture8::CDirect3DCubeTexture8(IDirect3DCubeTexture9* texture, CDirect3DDevice8* device)
: pCubeTexture9(texture)
, pDevice8(device)
{
}

CDirect3DCubeTexture8::~CDirect3DCubeTexture8()
{
}

HRESULT WINAPI CDirect3DCubeTexture8::QueryInterface(THIS_ REFIID riid, void** ppvObj)
{
	if (riid == IID_IUnknown
		|| riid == IID_IDirect3DResource8
		|| riid == IID_IDirect3DBaseTexture8 
		|| riid == IID_IDirect3DCubeTexture8)
	{
		AddRef();
		*ppvObj = this;
		return D3D_OK;
	}

	*ppvObj = NULL;
	return E_NOINTERFACE;
}

ULONG WINAPI CDirect3DCubeTexture8::AddRef(THIS)
{
	return pCubeTexture9->AddRef();
}

ULONG WINAPI CDirect3DCubeTexture8::Release(THIS)
{
	ULONG count = pCubeTexture9->Release();
	if (0 == count)
	{
		pDevice8->CubeTexturePool.Destory(pCubeTexture9);
		pCubeTexture9 = NULL;
		delete this;
	}
	return count;
}

STDMETHODIMP CDirect3DCubeTexture8::GetDevice(THIS_ IDirect3DDevice8** ppDevice)
{
	if (pDevice8 == NULL)
		return D3DERR_INVALIDCALL;
	pDevice8->AddRef();
	*ppDevice = pDevice8;
	return D3D_OK;
}

STDMETHODIMP CDirect3DCubeTexture8::SetPrivateData(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags)
{
	return pCubeTexture9->SetPrivateData(refguid, pData, SizeOfData, Flags);
}

STDMETHODIMP CDirect3DCubeTexture8::GetPrivateData(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData)
{
	return pCubeTexture9->GetPrivateData(refguid, pData, pSizeOfData);
}

STDMETHODIMP CDirect3DCubeTexture8::FreePrivateData(THIS_ REFGUID refguid)
{
	return pCubeTexture9->FreePrivateData(refguid);
}

STDMETHODIMP_(DWORD) CDirect3DCubeTexture8::SetPriority(THIS_ DWORD PriorityNew)
{
	return pCubeTexture9->SetPriority(PriorityNew);
}

STDMETHODIMP_(DWORD) CDirect3DCubeTexture8::GetPriority(THIS)
{
	return pCubeTexture9->GetPriority();
}

STDMETHODIMP_(void) CDirect3DCubeTexture8::PreLoad(THIS)
{
	pCubeTexture9->PreLoad();
}

STDMETHODIMP_(D3DRESOURCETYPE) CDirect3DCubeTexture8::GetType(THIS)
{
	return pCubeTexture9->GetType();
}

STDMETHODIMP_(DWORD) CDirect3DCubeTexture8::SetLOD(THIS_ DWORD LODNew)
{
	return pCubeTexture9->SetLOD(LODNew);
}

STDMETHODIMP_(DWORD) CDirect3DCubeTexture8::GetLOD(THIS)
{
	return pCubeTexture9->GetLOD();
}

STDMETHODIMP_(DWORD) CDirect3DCubeTexture8::GetLevelCount(THIS)
{
	return pCubeTexture9->GetLevelCount();
}

STDMETHODIMP CDirect3DCubeTexture8::GetLevelDesc(THIS_ UINT Level, D3D8SURFACE_DESC *pDesc)
{
	D3DSURFACE_DESC D3DDesc9;
	HRESULT hr = pCubeTexture9->GetLevelDesc(Level, &D3DDesc9);
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

STDMETHODIMP CDirect3DCubeTexture8::GetCubeMapSurface(THIS_ D3DCUBEMAP_FACES FaceType, UINT Level, IDirect3DSurface8** ppCubeMapSurface)
{
	IDirect3DSurface9* pCubeMapSurface9 = NULL;
	HRESULT hr = pCubeTexture9->GetCubeMapSurface(FaceType, Level, &pCubeMapSurface9);
	if (SUCCEEDED(hr))
	{
		*ppCubeMapSurface = pDevice8->SurfacePool.Create(pCubeMapSurface9, pDevice8);
	}
	return hr;
}

STDMETHODIMP CDirect3DCubeTexture8::LockRect(THIS_ D3DCUBEMAP_FACES FaceType, UINT Level, D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags)
{
	return pCubeTexture9->LockRect(FaceType, Level, pLockedRect, pRect, Flags);
}

STDMETHODIMP CDirect3DCubeTexture8::UnlockRect(THIS_ D3DCUBEMAP_FACES FaceType, UINT Level)
{
	return pCubeTexture9->UnlockRect(FaceType, Level);
}

STDMETHODIMP CDirect3DCubeTexture8::AddDirtyRect(THIS_ D3DCUBEMAP_FACES FaceType, CONST RECT* pDirtyRect)
{
	return pCubeTexture9->AddDirtyRect(FaceType, pDirtyRect);
}
