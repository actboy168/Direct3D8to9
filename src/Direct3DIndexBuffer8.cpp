#include "Direct3DIndexBuffer8.h"
#include "Direct3DDevice8.h"

CDirect3DIndexBuffer8::CDirect3DIndexBuffer8(IDirect3DIndexBuffer9* indexbuffer, CDirect3DDevice8* device) 
: pIndexBuffer9(indexbuffer)
, pDevice8(device)
{
}

CDirect3DIndexBuffer8::~CDirect3DIndexBuffer8()
{
	pDevice8->IndexBufferPool.Destory(pIndexBuffer9);
	pIndexBuffer9 = NULL;
}

HRESULT WINAPI CDirect3DIndexBuffer8::QueryInterface(THIS_ REFIID riid, void** ppvObj)
{
	if (riid == IID_IUnknown 
		|| riid == IID_IDirect3DResource8 
		|| riid == IID_IDirect3DIndexBuffer8)
	{
		AddRef();
		*ppvObj = this;
		return D3D_OK;
	}

	*ppvObj = NULL;
	return E_NOINTERFACE;
}

ULONG WINAPI CDirect3DIndexBuffer8::AddRef(THIS)
{
	return pIndexBuffer9->AddRef();
}

ULONG WINAPI CDirect3DIndexBuffer8::Release(THIS)
{
	ComptrGurad<IDirect3DIndexBuffer9> gurad(pIndexBuffer9);
	ULONG count = pIndexBuffer9->Release();
	if (1 == count)
	{
		delete this;
	}
	return count - 1;
}

STDMETHODIMP CDirect3DIndexBuffer8::GetDevice(THIS_ IDirect3DDevice8** ppDevice)
{
	if (pDevice8 == NULL)
		return D3DERR_INVALIDCALL;
	pDevice8->AddRef();
	*ppDevice = pDevice8;
	return D3D_OK;
}

STDMETHODIMP CDirect3DIndexBuffer8::SetPrivateData(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags)
{
	return pIndexBuffer9->SetPrivateData(refguid, pData, SizeOfData, Flags);
}

STDMETHODIMP CDirect3DIndexBuffer8::GetPrivateData(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData)
{
	return pIndexBuffer9->GetPrivateData(refguid, pData, pSizeOfData);
}

STDMETHODIMP CDirect3DIndexBuffer8::FreePrivateData(THIS_ REFGUID refguid)
{
	return pIndexBuffer9->FreePrivateData(refguid);
}

STDMETHODIMP_(DWORD) CDirect3DIndexBuffer8::SetPriority(THIS_ DWORD PriorityNew)
{
	return pIndexBuffer9->SetPriority(PriorityNew);
}

STDMETHODIMP_(DWORD) CDirect3DIndexBuffer8::GetPriority(THIS)
{
	return pIndexBuffer9->GetPriority();
}

STDMETHODIMP_(void) CDirect3DIndexBuffer8::PreLoad(THIS)
{
	pIndexBuffer9->PreLoad();
}

STDMETHODIMP_(D3DRESOURCETYPE) CDirect3DIndexBuffer8::GetType(THIS)
{
	return pIndexBuffer9->GetType();
}

STDMETHODIMP CDirect3DIndexBuffer8::Lock(THIS_ UINT OffsetToLock, UINT SizeToLock, BYTE** ppbData, DWORD Flags)
{
	return pIndexBuffer9->Lock(OffsetToLock, SizeToLock, (void**) ppbData, Flags);
}

STDMETHODIMP CDirect3DIndexBuffer8::Unlock(THIS)
{
	return pIndexBuffer9->Unlock();
}

STDMETHODIMP CDirect3DIndexBuffer8::GetDesc(THIS_ D3DINDEXBUFFER_DESC *pDesc)
{
	return pIndexBuffer9->GetDesc(pDesc);
}
