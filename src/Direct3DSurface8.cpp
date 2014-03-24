#include "Direct3DSurface8.h"
#include "Direct3DDevice8.h"

CDirect3DSurface8::CDirect3DSurface8(IDirect3DSurface9* surface, CDirect3DDevice8* device)
: pSurface9(surface)
, pDevice8(device)
{
}

HRESULT WINAPI CDirect3DSurface8::QueryInterface(THIS_ REFIID riid, void** ppvObj)
{
	if (riid == IID_IUnknown 
		|| riid == IID_IDirect3DSurface8)
	{
		*ppvObj = this;
	}

	*ppvObj = NULL;
	return E_NOINTERFACE;
}

ULONG WINAPI CDirect3DSurface8::AddRef(THIS)
{
	return pSurface9->AddRef();
}

ULONG WINAPI CDirect3DSurface8::Release(THIS)
{
	ULONG count = pSurface9->Release();
	if (0 == count)
	{
		pDevice8->SurfacePool.Destory(pSurface9);
		pSurface9 = NULL;
		delete this;
	}
	return count;
}

CDirect3DSurface8::~CDirect3DSurface8()
{
}

STDMETHODIMP CDirect3DSurface8::GetDevice(THIS_ IDirect3DDevice8** ppDevice)
{
	if (pDevice8 == NULL)
		return D3DERR_INVALIDCALL;
	pDevice8->AddRef();
	*ppDevice = pDevice8;
	return D3D_OK;
}

STDMETHODIMP CDirect3DSurface8::SetPrivateData(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags)
{
	return pSurface9->SetPrivateData(refguid, pData, SizeOfData, Flags);
}

STDMETHODIMP CDirect3DSurface8::GetPrivateData(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData)
{
	return pSurface9->GetPrivateData(refguid, pData, pSizeOfData);
}

STDMETHODIMP CDirect3DSurface8::FreePrivateData(THIS_ REFGUID refguid)
{
	return pSurface9->FreePrivateData(refguid);
}

STDMETHODIMP CDirect3DSurface8::GetContainer(THIS_ REFIID riid, void** ppContainer)
{
	return pSurface9->GetContainer(riid, ppContainer);
}

STDMETHODIMP CDirect3DSurface8::GetDesc(THIS_ D3D8SURFACE_DESC *pDesc)
{
	D3DSURFACE_DESC D3DDesc9;
	HRESULT hr = pSurface9->GetDesc(&D3DDesc9);
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

STDMETHODIMP CDirect3DSurface8::LockRect(THIS_ D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags)
{
	return pSurface9->LockRect(pLockedRect, pRect, Flags);
}

STDMETHODIMP CDirect3DSurface8::UnlockRect(THIS)
{
	return pSurface9->UnlockRect();
}
