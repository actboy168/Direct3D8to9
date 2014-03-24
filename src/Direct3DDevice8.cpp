#include "Direct3DDevice8.h"
#include "Direct3DBaseTexture8.h"
#include "Direct3DCubeTexture8.h"
#include "Direct3DIndexBuffer8.h"
#include "Direct3DSurface8.h"
#include "Direct3DSwapChain8.h"
#include "Direct3DTexture8.h"
#include "Direct3DVertexBuffer8.h"
#include "Direct3DVolumeTexture8.h"

CDirect3DDevice8::CDirect3DDevice8(IDirect3DDevice9* device, CDirect3D8* d3d)
: pDevice9(device)
, pDirect3D8(d3d)
, zBufferDiscardingEnabled(FALSE)
, baseVertexIndex(0)
{
	pDevice9->GetCreationParameters(&deviceCreationParameters);
}

CDirect3DDevice8::~CDirect3DDevice8()
{ }

HRESULT WINAPI CDirect3DDevice8::QueryInterface(THIS_ REFIID riid, void** ppvObj)
{
	if (riid == IID_IUnknown 
		|| riid == IID_IDirect3DDevice8)
	{
		AddRef();
		*ppvObj = this;
		return D3D_OK;
	}

	*ppvObj = NULL;
	return E_NOINTERFACE;
}

ULONG WINAPI CDirect3DDevice8::AddRef(THIS) 
{
	return pDevice9->AddRef();
}

ULONG WINAPI CDirect3DDevice8::Release(THIS)
{
	DWORD refCount = pDevice9->Release();
	if (0 == refCount)
	{
		pDirect3D8->DevicePool.Destory(pDevice9);
		pDevice9 = NULL;
		delete this;
	}
	return refCount;
}

HRESULT CDirect3DDevice8::SetZBufferDiscarding(bool IsEnabled)
{
	zBufferDiscardingEnabled = !!IsEnabled;
	return S_OK;
}

STDMETHODIMP CDirect3DDevice8::TestCooperativeLevel(THIS)
{
	return pDevice9->TestCooperativeLevel();
}

STDMETHODIMP_(UINT) CDirect3DDevice8::GetAvailableTextureMem(THIS)
{
	return pDevice9->GetAvailableTextureMem();
}

STDMETHODIMP CDirect3DDevice8::ResourceManagerDiscardBytes(THIS_ DWORD Bytes)
{
	return D3D_OK;
}

STDMETHODIMP CDirect3DDevice8::GetDirect3D(THIS_ IDirect3D8** ppD3D8)
{
	if (pDirect3D8 == NULL)
		return D3DERR_INVALIDCALL;
	pDirect3D8->AddRef();
	*ppD3D8 = pDirect3D8;
	return D3D_OK;
}

STDMETHODIMP CDirect3DDevice8::GetDeviceCaps(THIS_ D3DCAPS8* pCaps)
{
	D3DCAPS9 D3DCaps9;
	HRESULT result = pDevice9->GetDeviceCaps(&D3DCaps9);
	memcpy(pCaps, &D3DCaps9, sizeof(D3DCAPS8));
	return result;
}

STDMETHODIMP CDirect3DDevice8::GetDisplayMode(THIS_ D3DDISPLAYMODE* pMode)
{
	return pDevice9->GetDisplayMode(deviceCreationParameters.AdapterOrdinal, pMode);
}

STDMETHODIMP CDirect3DDevice8::GetCreationParameters(THIS_ D3DDEVICE_CREATION_PARAMETERS *pParameters)
{
	return pDevice9->GetCreationParameters(pParameters);
}

STDMETHODIMP CDirect3DDevice8::SetCursorProperties(THIS_ UINT XHotSpot, UINT YHotSpot, IDirect3DSurface8* pCursorBitmap)
{
	IDirect3DSurface9* pCursorBitmap9 = ((CDirect3DSurface8*)pCursorBitmap)->ToNine();
	return pDevice9->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap9);
}

STDMETHODIMP_(void) CDirect3DDevice8::SetCursorPosition(THIS_ int X, int Y, DWORD Flags)
{
	pDevice9->SetCursorPosition(X, Y, Flags);
}

STDMETHODIMP_(BOOL) CDirect3DDevice8::ShowCursor(THIS_ BOOL bShow)
{
	return pDevice9->ShowCursor(bShow);
}

STDMETHODIMP CDirect3DDevice8::CreateAdditionalSwapChain(THIS_ D3D8PRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain8** pSwapChain)
{
	IDirect3D9* pDirect3D9 = NULL;
	HRESULT hr = pDevice9->GetDirect3D(&pDirect3D9);
	if (SUCCEEDED(hr))
	{
		D3DPRESENT_PARAMETERS D3DPresentationParameters9;
		ZeroMemory(&D3DPresentationParameters9, sizeof(D3DPresentationParameters9));
		D3DPresentationParameters9.AutoDepthStencilFormat = pPresentationParameters->AutoDepthStencilFormat;
		D3DPresentationParameters9.BackBufferCount = pPresentationParameters->BackBufferCount;
		D3DPresentationParameters9.BackBufferFormat = pPresentationParameters->BackBufferFormat;
		D3DPresentationParameters9.BackBufferHeight = pPresentationParameters->BackBufferHeight;
		D3DPresentationParameters9.BackBufferWidth = pPresentationParameters->BackBufferWidth;
		D3DPresentationParameters9.EnableAutoDepthStencil = pPresentationParameters->EnableAutoDepthStencil;
		D3DPresentationParameters9.Flags = pPresentationParameters->Flags;
		D3DPresentationParameters9.FullScreen_RefreshRateInHz = pPresentationParameters->FullScreen_RefreshRateInHz;
		D3DPresentationParameters9.hDeviceWindow = pPresentationParameters->hDeviceWindow;
		D3DPresentationParameters9.MultiSampleQuality = 0;
		D3DPresentationParameters9.MultiSampleType = pPresentationParameters->MultiSampleType;
		D3DPresentationParameters9.PresentationInterval = pPresentationParameters->FullScreen_PresentationInterval;
		D3DPresentationParameters9.SwapEffect = pPresentationParameters->SwapEffect;
		D3DPresentationParameters9.Windowed = pPresentationParameters->Windowed;

		IDirect3DSwapChain9* pSwapChain9 = NULL;
		hr = pDevice9->CreateAdditionalSwapChain(&D3DPresentationParameters9, &pSwapChain9);
		if (SUCCEEDED(hr))
		{
			*pSwapChain = SwapChainPool.Create(pSwapChain9, this);
		}
		pDirect3D9->Release();
	}

	return hr;
}

STDMETHODIMP CDirect3DDevice8::Reset(THIS_ D3D8PRESENT_PARAMETERS* pPresentationParameters)
{
	IDirect3D9* pDirect3D9 = NULL;
	HRESULT hr = pDevice9->GetDirect3D(&pDirect3D9);
	if (SUCCEEDED(hr))
	{
		D3DPRESENT_PARAMETERS D3DPresentationParameters9;
		ZeroMemory(&D3DPresentationParameters9, sizeof(D3DPresentationParameters9));
		D3DPresentationParameters9.AutoDepthStencilFormat = pPresentationParameters->AutoDepthStencilFormat;
		D3DPresentationParameters9.BackBufferCount = pPresentationParameters->BackBufferCount;
		D3DPresentationParameters9.BackBufferFormat = pPresentationParameters->BackBufferFormat;
		D3DPresentationParameters9.BackBufferHeight = pPresentationParameters->BackBufferHeight;
		D3DPresentationParameters9.BackBufferWidth = pPresentationParameters->BackBufferWidth;
		D3DPresentationParameters9.EnableAutoDepthStencil = pPresentationParameters->EnableAutoDepthStencil;
		D3DPresentationParameters9.Flags = pPresentationParameters->Flags;
		D3DPresentationParameters9.FullScreen_RefreshRateInHz = pPresentationParameters->FullScreen_RefreshRateInHz;
		D3DPresentationParameters9.hDeviceWindow = pPresentationParameters->hDeviceWindow;
		D3DPresentationParameters9.MultiSampleQuality = 0;
		D3DPresentationParameters9.MultiSampleType = pPresentationParameters->MultiSampleType;
		D3DPresentationParameters9.PresentationInterval = pPresentationParameters->FullScreen_PresentationInterval;
		D3DPresentationParameters9.SwapEffect = pPresentationParameters->SwapEffect;
		D3DPresentationParameters9.Windowed = pPresentationParameters->Windowed;
		hr = pDevice9->Reset(&D3DPresentationParameters9);
		pDirect3D9->Release();
	}

	return hr;
}

STDMETHODIMP CDirect3DDevice8::Present(THIS_ CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
	return pDevice9->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

STDMETHODIMP CDirect3DDevice8::GetBackBuffer(THIS_ UINT BackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface8** ppBackBuffer)
{
	IDirect3DSurface9* pBackBuffer9 = NULL;
	HRESULT hr = pDevice9->GetBackBuffer(deviceCreationParameters.AdapterOrdinal, BackBuffer, Type, &pBackBuffer9);
	if (SUCCEEDED(hr))
	{
		*ppBackBuffer = SurfacePool.Create(pBackBuffer9, this);
	}
	return hr;
}

STDMETHODIMP CDirect3DDevice8::GetRasterStatus(THIS_ D3DRASTER_STATUS* pRasterStatus)
{
	return pDevice9->GetRasterStatus(deviceCreationParameters.AdapterOrdinal, pRasterStatus);
}

STDMETHODIMP_(void) CDirect3DDevice8::SetGammaRamp(THIS_ DWORD Flags, CONST D3DGAMMARAMP* pRamp)
{
	pDevice9->SetGammaRamp(deviceCreationParameters.AdapterOrdinal, Flags, pRamp);
}

STDMETHODIMP_(void) CDirect3DDevice8::GetGammaRamp(THIS_ D3DGAMMARAMP* pRamp)
{
	pDevice9->GetGammaRamp(deviceCreationParameters.AdapterOrdinal, pRamp);
}

STDMETHODIMP CDirect3DDevice8::CreateTexture(THIS_ UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture8** ppTexture)
{
	IDirect3DTexture9* pTexture9 = NULL;
	HRESULT hr = pDevice9->CreateTexture(Width, Height, Levels, Usage, Format, Pool, &pTexture9, NULL);
	if (SUCCEEDED(hr))
	{
		*ppTexture = TexturePool.Create(pTexture9, this);
	}
	return hr;
}

STDMETHODIMP CDirect3DDevice8::CreateVolumeTexture(THIS_ UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture8** ppVolumeTexture)
{
	IDirect3DVolumeTexture9* pVolumeTexture9 = NULL;
	HRESULT hr = pDevice9->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, &pVolumeTexture9, NULL);
	if (SUCCEEDED(hr))
	{
		*ppVolumeTexture = VolumeTexturePool.Create(pVolumeTexture9, this);
	}
	return hr;
}

STDMETHODIMP CDirect3DDevice8::CreateCubeTexture(THIS_ UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture8** ppCubeTexture)
{
	IDirect3DCubeTexture9* pCubeTexture9 = NULL;
	HRESULT hr = pDevice9->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, &pCubeTexture9, NULL);
	if (SUCCEEDED(hr))
	{
		*ppCubeTexture = CubeTexturePool.Create(pCubeTexture9, this);
	}
	return hr;
}

STDMETHODIMP CDirect3DDevice8::CreateVertexBuffer(THIS_ UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer8** ppVertexBuffer)
{
	IDirect3DVertexBuffer9* pVertexBuffer9 = NULL;
	HRESULT hr = pDevice9->CreateVertexBuffer(Length, Usage, FVF, Pool, &pVertexBuffer9, NULL);
	if (SUCCEEDED(hr))
	{
		*ppVertexBuffer = VertexBufferPool.Create(pVertexBuffer9, this);
	}
	return hr;
}

STDMETHODIMP CDirect3DDevice8::CreateIndexBuffer(THIS_ UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer8** ppIndexBuffer)
{
	IDirect3DIndexBuffer9* pIndexBuffer9 = NULL;
	HRESULT hr = pDevice9->CreateIndexBuffer(Length, Usage, Format, Pool, &pIndexBuffer9, NULL);
	if (SUCCEEDED(hr))
	{
		*ppIndexBuffer = IndexBufferPool.Create(pIndexBuffer9, this);
	}
	return hr;
}

STDMETHODIMP CDirect3DDevice8::CreateRenderTarget(THIS_ UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, BOOL Lockable, IDirect3DSurface8** ppSurface)
{
	IDirect3D9* pDirect3D9 = NULL;
	HRESULT hr = pDevice9->GetDirect3D(&pDirect3D9);
	if (SUCCEEDED(hr))
	{
		DWORD multiSampleQuality;
		hr = pDirect3D9->CheckDeviceMultiSampleType(deviceCreationParameters.AdapterOrdinal, deviceCreationParameters.DeviceType, Format, TRUE, MultiSample, &multiSampleQuality);
		if (SUCCEEDED(hr))
		{
			IDirect3DSurface9* pSurface9 = NULL;
			hr = pDevice9->CreateRenderTarget(Width, Height, Format, MultiSample, multiSampleQuality, Lockable, &pSurface9, NULL);
			if (SUCCEEDED(hr))
			{
				*ppSurface = SurfacePool.Create(pSurface9, this);
			}
		}

		pDirect3D9->Release();
	}

	return hr;
}

STDMETHODIMP CDirect3DDevice8::CreateDepthStencilSurface(THIS_ UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, IDirect3DSurface8** ppSurface)
{
	IDirect3D9* pDirect3D9 = NULL;
	HRESULT hr = pDevice9->GetDirect3D(&pDirect3D9);
	if (SUCCEEDED(hr))
	{
		DWORD multiSampleQuality;
		hr = pDirect3D9->CheckDeviceMultiSampleType(deviceCreationParameters.AdapterOrdinal, deviceCreationParameters.DeviceType, Format, TRUE, MultiSample, &multiSampleQuality);
		if (SUCCEEDED(hr))
		{
			IDirect3DSurface9* pSurface9 = NULL;
			hr = pDevice9->CreateDepthStencilSurface(Width, Height, Format, MultiSample, multiSampleQuality, zBufferDiscardingEnabled, &pSurface9, NULL);
			if (SUCCEEDED(hr))
			{
				*ppSurface = SurfacePool.Create(pSurface9, this);
			}
		}

		pDirect3D9->Release();
	}

	return hr;
}

STDMETHODIMP CDirect3DDevice8::CreateImageSurface(THIS_ UINT Width, UINT Height, D3DFORMAT Format, IDirect3DSurface8** ppSurface)
{
	IDirect3DSurface9* pSurface9 = NULL;
	HRESULT hr = pDevice9->CreateOffscreenPlainSurface(Width, Height, Format, D3DPOOL_SCRATCH, &pSurface9, NULL);
	if (SUCCEEDED(hr))
	{
		*ppSurface = SurfacePool.Create(pSurface9, this);
	}
	return hr;
}

STDMETHODIMP CDirect3DDevice8::CopyRects(THIS_ IDirect3DSurface8* pSourceSurface, CONST RECT* pSourceRectsArray, UINT cRects, IDirect3DSurface8* pDestinationSurface, CONST POINT* pDestPointsArray)
{
	HRESULT result = D3DERR_INVALIDCALL;

	IDirect3DSurface9* pSourceSurface9 = ((CDirect3DSurface8*)pSourceSurface)->ToNine();
	IDirect3DSurface9* pDestinationSurface9 = ((CDirect3DSurface8*)pDestinationSurface)->ToNine();

	if (pSourceRectsArray == NULL)
	{
		if (pDestPointsArray == NULL)
		{
			POINT pt = { 0, 0 };
			result = pDevice9->UpdateSurface(pSourceSurface9, NULL, pDestinationSurface9, &pt);
		}
		else
		{
			result = pDevice9->UpdateSurface(pSourceSurface9, NULL, pDestinationSurface9, pDestPointsArray);
		}
	}
	else
	{
		if (pDestPointsArray == NULL)
		{
			POINT pt = { 0, 0 };
			for (UINT i = 0; i < cRects; i++)
			{
				result = pDevice9->UpdateSurface(pSourceSurface9, &pSourceRectsArray[i], pDestinationSurface9, &pt);
				if (!SUCCEEDED(result))
				{
					break;
				}
			}
		}
		else
		{
			for (UINT i = 0; i < cRects; i++)
			{
				result = pDevice9->UpdateSurface(pSourceSurface9, &pSourceRectsArray[i], pDestinationSurface9, &pDestPointsArray[i]);
				if (!SUCCEEDED(result))
				{
					break;
				}
			}
		}
	}

	return result;
}

STDMETHODIMP CDirect3DDevice8::UpdateTexture(THIS_ IDirect3DBaseTexture8* pSourceTexture, IDirect3DBaseTexture8* pDestinationTexture)
{
	IDirect3DBaseTexture9* pSourceTexture9 = ((CDirect3DBaseTexture8*)pSourceTexture)->ToNine();
	IDirect3DBaseTexture9* pDestinationTexture9 = ((CDirect3DBaseTexture8*)pDestinationTexture)->ToNine();
	return pDevice9->UpdateTexture(pSourceTexture9, pDestinationTexture9);
}

STDMETHODIMP CDirect3DDevice8::GetFrontBuffer(THIS_ IDirect3DSurface8* pDestSurface)
{
	IDirect3DSurface9* pDestSurface9 = ((CDirect3DSurface8*)pDestSurface)->ToNine();
	return pDevice9->GetFrontBufferData(deviceCreationParameters.AdapterOrdinal, pDestSurface9);
}

STDMETHODIMP CDirect3DDevice8::SetRenderTarget(THIS_ IDirect3DSurface8* pRenderTarget, IDirect3DSurface8* pNewZStencil)
{
	if (pRenderTarget == NULL)
	{
		IDirect3DSurface9* pNewZStencil9 = ((CDirect3DSurface8*)pNewZStencil)->ToNine();
		return pDevice9->SetDepthStencilSurface(pNewZStencil9);
	}

	IDirect3DSurface9* pRenderTarget9 = ((CDirect3DSurface8*)pRenderTarget)->ToNine();
	HRESULT hr = pDevice9->SetRenderTarget(0, pRenderTarget9);
	if (pNewZStencil != NULL)
	{
		IDirect3DSurface9* pNewZStencil9 = ((CDirect3DSurface8*)pNewZStencil)->ToNine();
		hr = pDevice9->SetDepthStencilSurface(pNewZStencil9);
	}

	return hr;
}

STDMETHODIMP CDirect3DDevice8::GetRenderTarget(THIS_ IDirect3DSurface8** ppRenderTarget)
{
	IDirect3DSurface9* pSurface9 = NULL;
	HRESULT hr = pDevice9->GetRenderTarget(0, &pSurface9);
	if (SUCCEEDED(hr))
	{
		*ppRenderTarget = SurfacePool.Create(pSurface9, this);
	}
	return hr;
}

STDMETHODIMP CDirect3DDevice8::GetDepthStencilSurface(THIS_ IDirect3DSurface8** ppZStencilSurface)
{
	IDirect3DSurface9* pSurface9 = NULL;
	HRESULT hr = pDevice9->GetDepthStencilSurface(&pSurface9);
	if (SUCCEEDED(hr))
	{
		*ppZStencilSurface = SurfacePool.Create(pSurface9, this);
	}
	return hr;
}

STDMETHODIMP CDirect3DDevice8::BeginScene(THIS)
{
	return pDevice9->BeginScene();
}

STDMETHODIMP CDirect3DDevice8::EndScene(THIS)
{
	return pDevice9->EndScene();
}

STDMETHODIMP CDirect3DDevice8::Clear(THIS_ DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
	return pDevice9->Clear(Count, pRects, Flags, Color, Z, Stencil);
}

STDMETHODIMP CDirect3DDevice8::SetTransform(THIS_ D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix)
{
	return pDevice9->SetTransform(State, pMatrix);
}

STDMETHODIMP CDirect3DDevice8::GetTransform(THIS_ D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix)
{
	return pDevice9->GetTransform(State, pMatrix);
}

STDMETHODIMP CDirect3DDevice8::MultiplyTransform(THIS_ D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix)
{
	return pDevice9->MultiplyTransform(State, pMatrix);
}

STDMETHODIMP CDirect3DDevice8::SetViewport(THIS_ CONST D3DVIEWPORT8* pViewport)
{
	return pDevice9->SetViewport(pViewport);
}

STDMETHODIMP CDirect3DDevice8::GetViewport(THIS_ D3DVIEWPORT8* pViewport)
{
	return pDevice9->GetViewport(pViewport);
}

STDMETHODIMP CDirect3DDevice8::SetMaterial(THIS_ CONST D3DMATERIAL8* pMaterial)
{
	return pDevice9->SetMaterial(pMaterial);
}

STDMETHODIMP CDirect3DDevice8::GetMaterial(THIS_ D3DMATERIAL8* pMaterial)
{
	return pDevice9->GetMaterial(pMaterial);
}

STDMETHODIMP CDirect3DDevice8::SetLight(THIS_ DWORD Index, CONST D3DLIGHT8* pLight)
{
	return pDevice9->SetLight(Index, pLight);
}

STDMETHODIMP CDirect3DDevice8::GetLight(THIS_ DWORD Index, D3DLIGHT8* pLight)
{
	return pDevice9->GetLight(Index, pLight);
}

STDMETHODIMP CDirect3DDevice8::LightEnable(THIS_ DWORD Index, BOOL Enable)
{
	return pDevice9->LightEnable(Index, Enable);
}

STDMETHODIMP CDirect3DDevice8::GetLightEnable(THIS_ DWORD Index, BOOL* pEnable)
{
	return pDevice9->GetLightEnable(Index, pEnable);
}

STDMETHODIMP CDirect3DDevice8::SetClipPlane(THIS_ DWORD Index, CONST float* pPlane)
{
	return pDevice9->SetClipPlane(Index, pPlane);
}

STDMETHODIMP CDirect3DDevice8::GetClipPlane(THIS_ DWORD Index, float* pPlane)
{
	return pDevice9->GetClipPlane(Index, pPlane);
}

STDMETHODIMP CDirect3DDevice8::SetRenderState(THIS_ D3DRENDERSTATETYPE State, DWORD Value)
{
	return pDevice9->SetRenderState(State, Value);
}

STDMETHODIMP CDirect3DDevice8::GetRenderState(THIS_ D3DRENDERSTATETYPE State, DWORD* pValue)
{
	return pDevice9->GetRenderState(State, pValue);
}

STDMETHODIMP CDirect3DDevice8::BeginStateBlock(THIS)
{
	return pDevice9->BeginStateBlock();
}

STDMETHODIMP CDirect3DDevice8::EndStateBlock(THIS_ DWORD* pToken)
{
	return pDevice9->EndStateBlock((IDirect3DStateBlock9**)pToken);
}

STDMETHODIMP CDirect3DDevice8::ApplyStateBlock(THIS_ DWORD Token)
{
	IDirect3DStateBlock9* pBlock = (IDirect3DStateBlock9*)Token;
	return pBlock->Apply();
}

STDMETHODIMP CDirect3DDevice8::CaptureStateBlock(THIS_ DWORD Token)
{
	IDirect3DStateBlock9* pBlock = (IDirect3DStateBlock9*)Token;
	return pBlock->Capture();
}

STDMETHODIMP CDirect3DDevice8::DeleteStateBlock(THIS_ DWORD Token)
{
	IDirect3DStateBlock9* pBlock = (IDirect3DStateBlock9*)Token;
	pBlock->Release();
	return D3D_OK;
}

STDMETHODIMP CDirect3DDevice8::CreateStateBlock(THIS_ D3DSTATEBLOCKTYPE Type, DWORD* pToken)
{
	return pDevice9->CreateStateBlock(Type, (IDirect3DStateBlock9**)pToken);
}

STDMETHODIMP CDirect3DDevice8::SetClipStatus(THIS_ CONST D3DCLIPSTATUS8* pClipStatus)
{
	return pDevice9->SetClipStatus(pClipStatus);
}

STDMETHODIMP CDirect3DDevice8::GetClipStatus(THIS_ D3DCLIPSTATUS8* pClipStatus)
{
	return pDevice9->GetClipStatus(pClipStatus);
}

STDMETHODIMP CDirect3DDevice8::GetTexture(THIS_ DWORD Stage, IDirect3DBaseTexture8** ppTexture)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::SetTexture(THIS_ DWORD Stage, IDirect3DBaseTexture8* pTexture)
{
	IDirect3DBaseTexture9* pTexture9 = ((CDirect3DBaseTexture8*)pTexture)->ToNine();
	return pDevice9->SetTexture(Stage, pTexture9);
}

STDMETHODIMP CDirect3DDevice8::GetTextureStageState(THIS_ DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue)
{
	return pDevice9->GetTextureStageState(Stage, Type, pValue);
}

STDMETHODIMP CDirect3DDevice8::SetTextureStageState(THIS_ DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
	return pDevice9->SetTextureStageState(Stage, Type, Value);
}

STDMETHODIMP CDirect3DDevice8::ValidateDevice(THIS_ DWORD* pNumPasses)
{
	return pDevice9->ValidateDevice(pNumPasses);
}

STDMETHODIMP CDirect3DDevice8::GetInfo(THIS_ DWORD DevInfoID, void* pDevInfoStruct, DWORD DevInfoStructSize)
{
	// see http://msdn.microsoft.com/en-us/library/ms889650.aspx
	return S_FALSE;
}

STDMETHODIMP CDirect3DDevice8::SetPaletteEntries(THIS_ UINT PaletteNumber, CONST PALETTEENTRY* pEntries)
{
	return pDevice9->SetPaletteEntries(PaletteNumber, pEntries);
}

STDMETHODIMP CDirect3DDevice8::GetPaletteEntries(THIS_ UINT PaletteNumber, PALETTEENTRY* pEntries)
{
	return pDevice9->GetPaletteEntries(PaletteNumber, pEntries);
}

STDMETHODIMP CDirect3DDevice8::SetCurrentTexturePalette(THIS_ UINT PaletteNumber)
{
	return pDevice9->SetCurrentTexturePalette(PaletteNumber);
}

STDMETHODIMP CDirect3DDevice8::GetCurrentTexturePalette(THIS_ UINT *PaletteNumber)
{
	return pDevice9->GetCurrentTexturePalette(PaletteNumber);
}

STDMETHODIMP CDirect3DDevice8::DrawPrimitive(THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	return pDevice9->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

STDMETHODIMP CDirect3DDevice8::DrawIndexedPrimitive(THIS_ D3DPRIMITIVETYPE Type, UINT minIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	return pDevice9->DrawIndexedPrimitive(Type, baseVertexIndex, minIndex, NumVertices, startIndex, primCount);
}

STDMETHODIMP CDirect3DDevice8::DrawPrimitiveUP(THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return pDevice9->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

STDMETHODIMP CDirect3DDevice8::DrawIndexedPrimitiveUP(THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertexIndices, UINT PrimitiveCount, CONST void* pIndexData, D3DFORMAT IndexDataFormat, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return pDevice9->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertexIndices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}

STDMETHODIMP CDirect3DDevice8::ProcessVertices(THIS_ UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer8* pDestBuffer, DWORD Flags)
{
	IDirect3DVertexBuffer9* pDestBuffer9 = ((CDirect3DVertexBuffer8*)pDestBuffer)->ToNine();
	return pDevice9->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer9, NULL, Flags);
}

STDMETHODIMP CDirect3DDevice8::CreateVertexShader(THIS_ CONST DWORD* pDeclaration, CONST DWORD* pFunction, DWORD* pHandle, DWORD Usage)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::SetVertexShader(THIS_ DWORD Handle)
{
	return pDevice9->SetFVF(Handle);
}

STDMETHODIMP CDirect3DDevice8::GetVertexShader(THIS_ DWORD* pHandle)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::DeleteVertexShader(THIS_ DWORD Handle)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::SetVertexShaderConstant(THIS_ DWORD Register, CONST void* pConstantData, DWORD ConstantCount)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::GetVertexShaderConstant(THIS_ DWORD Register, void* pConstantData, DWORD ConstantCount)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::GetVertexShaderDeclaration(THIS_ DWORD Handle, void* pData, DWORD* pSizeOfData)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::GetVertexShaderFunction(THIS_ DWORD Handle, void* pData, DWORD* pSizeOfData)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::SetStreamSource(THIS_ UINT StreamNumber, IDirect3DVertexBuffer8* pStreamData, UINT Stride)
{
	IDirect3DVertexBuffer9* pStreamData9 = ((CDirect3DVertexBuffer8*)pStreamData)->ToNine();
	return pDevice9->SetStreamSource(StreamNumber, pStreamData9, 0, Stride);
}

STDMETHODIMP CDirect3DDevice8::GetStreamSource(THIS_ UINT StreamNumber, IDirect3DVertexBuffer8** ppStreamData, UINT* pStride)
{
	IDirect3DVertexBuffer9* pStreamData9 = NULL;
	HRESULT hr = pDevice9->GetStreamSource(StreamNumber, &pStreamData9, NULL, pStride);
	if (SUCCEEDED(hr))
	{
		*ppStreamData = VertexBufferPool.Create(pStreamData9, this);
	}
	return hr;
}

STDMETHODIMP CDirect3DDevice8::SetIndices(THIS_ IDirect3DIndexBuffer8* pIndexData, UINT BaseVertexIndex)
{
	baseVertexIndex = BaseVertexIndex;
	IDirect3DIndexBuffer9* pIndexData9 = ((CDirect3DIndexBuffer8*)pIndexData)->ToNine();
	return pDevice9->SetIndices(pIndexData9);
}

STDMETHODIMP CDirect3DDevice8::GetIndices(THIS_ IDirect3DIndexBuffer8** ppIndexData, UINT* pBaseVertexIndex)
{
	if (!ppIndexData)
	{
		return D3DERR_INVALIDCALL;
	}

	IDirect3DIndexBuffer9* pIndexData9 = NULL;
	HRESULT hr = pDevice9->GetIndices(&pIndexData9);
	if (SUCCEEDED(hr))
	{
		*ppIndexData = IndexBufferPool.Create(pIndexData9, this);
		if (pBaseVertexIndex) *pBaseVertexIndex = baseVertexIndex;
	}
	return hr;
}

STDMETHODIMP CDirect3DDevice8::CreatePixelShader(THIS_ CONST DWORD* pFunction, DWORD* pHandle)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::SetPixelShader(THIS_ DWORD Handle)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::GetPixelShader(THIS_ DWORD* pHandle)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::DeletePixelShader(THIS_ DWORD Handle)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::SetPixelShaderConstant(THIS_ DWORD Register, CONST void* pConstantData, DWORD ConstantCount)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::GetPixelShaderConstant(THIS_ DWORD Register, void* pConstantData, DWORD ConstantCount)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::GetPixelShaderFunction(THIS_ DWORD Handle, void* pData, DWORD* pSizeOfData)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::DrawRectPatch(THIS_ UINT Handle, CONST float* pNumSegs, CONST D3DRECTPATCH_INFO* pRectPatchInfo)
{
	return pDevice9->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}

STDMETHODIMP CDirect3DDevice8::DrawTriPatch(THIS_ UINT Handle, CONST float* pNumSegs, CONST D3DTRIPATCH_INFO* pTriPatchInfo)
{
	return pDevice9->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}

STDMETHODIMP CDirect3DDevice8::DeletePatch(THIS_ UINT Handle)
{
	return pDevice9->DeletePatch(Handle);
}
