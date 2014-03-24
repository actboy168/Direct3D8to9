#include "Direct3DBaseTexture8.h"
#include "Direct3DDevice8.h"

CDirect3DBaseTexture8::CDirect3DBaseTexture8(IDirect3DBaseTexture9* texture, CDirect3DDevice8* device)
: pBaseTexture9(texture)
, pDevice8(device)
{
}

CDirect3DBaseTexture8::~CDirect3DBaseTexture8()
{
}

HRESULT WINAPI CDirect3DBaseTexture8::QueryInterface(THIS_ REFIID riid, void** ppvObj)
{
	if (riid == IID_IUnknown
		|| riid == IID_IDirect3DResource8
		|| riid == IID_IDirect3DBaseTexture8)
	{
		*ppvObj = this;
	}

	*ppvObj = NULL;
	return E_NOINTERFACE;
}

ULONG WINAPI CDirect3DBaseTexture8::AddRef(THIS)
{
	return pBaseTexture9->AddRef();
}

ULONG WINAPI CDirect3DBaseTexture8::Release(THIS)
{
	ULONG count = pBaseTexture9->Release();
	if (0 == count)
	{
		pBaseTexture9 = NULL;
		delete this;
	}
	return count;
}

STDMETHODIMP CDirect3DBaseTexture8::GetDevice(THIS_ IDirect3DDevice8** ppDevice)
{
	if (pDevice8 == NULL)
		return D3DERR_INVALIDCALL;
	pDevice8->AddRef();
	*ppDevice = pDevice8;
	return D3D_OK;
}

STDMETHODIMP CDirect3DBaseTexture8::SetPrivateData(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags)
{
	return pBaseTexture9->SetPrivateData(refguid, pData, SizeOfData, Flags);
}

STDMETHODIMP CDirect3DBaseTexture8::GetPrivateData(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData)
{
	return pBaseTexture9->GetPrivateData(refguid, pData, pSizeOfData);
}

STDMETHODIMP CDirect3DBaseTexture8::FreePrivateData(THIS_ REFGUID refguid)
{
	return pBaseTexture9->FreePrivateData(refguid);
}

STDMETHODIMP_(DWORD) CDirect3DBaseTexture8::SetPriority(THIS_ DWORD PriorityNew)
{
	return pBaseTexture9->SetPriority(PriorityNew);
}

STDMETHODIMP_(DWORD) CDirect3DBaseTexture8::GetPriority(THIS)
{
	return pBaseTexture9->GetPriority();
}

STDMETHODIMP_(void) CDirect3DBaseTexture8::PreLoad(THIS)
{
	pBaseTexture9->PreLoad();
}

STDMETHODIMP_(D3DRESOURCETYPE) CDirect3DBaseTexture8::GetType(THIS)
{
	return pBaseTexture9->GetType();
}

STDMETHODIMP_(DWORD) CDirect3DBaseTexture8::SetLOD(THIS_ DWORD LODNew)
{
	return pBaseTexture9->SetLOD(LODNew);
}

STDMETHODIMP_(DWORD) CDirect3DBaseTexture8::GetLOD(THIS)
{
	return pBaseTexture9->GetLOD();
}

STDMETHODIMP_(DWORD) CDirect3DBaseTexture8::GetLevelCount(THIS)
{
	return pBaseTexture9->GetLevelCount();
}
