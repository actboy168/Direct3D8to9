#include "Direct3DSwapChain8.h"
#include "Direct3DDevice8.h"
#include "Direct3DSurface8.h"

CDirect3DSwapChain8::CDirect3DSwapChain8(IDirect3DSwapChain9* swapchain, CDirect3DDevice8* device)
: pSwapChain9(swapchain)
, pDevice8(device)
{
}

CDirect3DSwapChain8::~CDirect3DSwapChain8()
{
	pDevice8->SwapChainPool.Destory(pSwapChain9);
	pSwapChain9 = NULL;
}

HRESULT WINAPI CDirect3DSwapChain8::QueryInterface(THIS_ REFIID riid, void** ppvObj)
{
	if (riid == IID_IUnknown
		|| riid == IID_IDirect3DSwapChain8)
	{
		AddRef();
		*ppvObj = this;
		return D3D_OK;
	}

	*ppvObj = NULL;
	return E_NOINTERFACE;
}

ULONG WINAPI CDirect3DSwapChain8::AddRef(THIS)
{
	return pSwapChain9->AddRef();
}

ULONG WINAPI CDirect3DSwapChain8::Release(THIS)
{
	ComptrGurad<IDirect3DSwapChain9> gurad(pSwapChain9);
	ULONG count = pSwapChain9->Release();
	if (1 == count)
	{
		delete this;
	}
	return count - 1;
}

STDMETHODIMP CDirect3DSwapChain8::Present(THIS_ CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
	return pSwapChain9->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion, 0);
}

STDMETHODIMP CDirect3DSwapChain8::GetBackBuffer(THIS_ UINT BackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface8** ppBackBuffer)
{
	IDirect3DSurface9* pBackBuffer9 = NULL;
	HRESULT hr = pSwapChain9->GetBackBuffer(BackBuffer, Type, &pBackBuffer9);
	if (SUCCEEDED(hr))
	{
		*ppBackBuffer = pDevice8->SurfacePool.Create(pBackBuffer9, pDevice8);
	}
	return hr;
}
