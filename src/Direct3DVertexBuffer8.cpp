#include "Direct3DVertexBuffer8.h"
#include "Direct3DDevice8.h"

CDirect3DVertexBuffer8::CDirect3DVertexBuffer8(IDirect3DVertexBuffer9* vertexbuffer, CDirect3DDevice8* device)
: pVertexBuffer9(vertexbuffer)
, pDevice8(device)
{
}

CDirect3DVertexBuffer8::~CDirect3DVertexBuffer8()
{
}

HRESULT WINAPI CDirect3DVertexBuffer8::QueryInterface(THIS_ REFIID riid, void** ppvObj)
{
	if (riid == IID_IUnknown
		|| riid == IID_IDirect3DResource8 
		|| riid == IID_IDirect3DVertexBuffer8)
	{
		*ppvObj = this;
	}

	*ppvObj = NULL;
	return E_NOINTERFACE;
}

ULONG WINAPI CDirect3DVertexBuffer8::AddRef(THIS)
{
	return pVertexBuffer9->AddRef();
}

ULONG WINAPI CDirect3DVertexBuffer8::Release(THIS)
{
	ULONG count = pVertexBuffer9->Release();
	if (0 == count)
	{
		pDevice8->VertexBufferPool.Destory(pVertexBuffer9);
		pVertexBuffer9 = NULL;
		delete this;
	}
	return count;
}

STDMETHODIMP CDirect3DVertexBuffer8::GetDevice(THIS_ IDirect3DDevice8** ppDevice)
{
	if (pDevice8 == NULL)
		return D3DERR_INVALIDCALL;
	pDevice8->AddRef();
	*ppDevice = pDevice8;
	return D3D_OK;
}

STDMETHODIMP CDirect3DVertexBuffer8::SetPrivateData(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags)
{
	return pVertexBuffer9->SetPrivateData(refguid, pData, SizeOfData, Flags);
}

STDMETHODIMP CDirect3DVertexBuffer8::GetPrivateData(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData)
{
	return pVertexBuffer9->GetPrivateData(refguid, pData, pSizeOfData);
}

STDMETHODIMP CDirect3DVertexBuffer8::FreePrivateData(THIS_ REFGUID refguid)
{
	return pVertexBuffer9->FreePrivateData(refguid);
}

STDMETHODIMP_(DWORD) CDirect3DVertexBuffer8::SetPriority(THIS_ DWORD PriorityNew)
{
	return pVertexBuffer9->SetPriority(PriorityNew);
}

STDMETHODIMP_(DWORD) CDirect3DVertexBuffer8::GetPriority(THIS)
{
	return pVertexBuffer9->GetPriority();
}

STDMETHODIMP_(void) CDirect3DVertexBuffer8::PreLoad(THIS)
{
	pVertexBuffer9->PreLoad();
}

STDMETHODIMP_(D3DRESOURCETYPE) CDirect3DVertexBuffer8::GetType(THIS)
{
	return pVertexBuffer9->GetType();
}

STDMETHODIMP CDirect3DVertexBuffer8::Lock(THIS_ UINT OffsetToLock, UINT SizeToLock, BYTE** ppbData, DWORD Flags)
{
	return pVertexBuffer9->Lock(OffsetToLock, SizeToLock, (void**) ppbData, Flags);
}

STDMETHODIMP CDirect3DVertexBuffer8::Unlock(THIS)
{
	return pVertexBuffer9->Unlock();
}

STDMETHODIMP CDirect3DVertexBuffer8::GetDesc(THIS_ D3DVERTEXBUFFER_DESC *pDesc)
{
	return pVertexBuffer9->GetDesc(pDesc);
}
