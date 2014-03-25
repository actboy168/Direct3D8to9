#include "Direct3D8.h"
#include "Direct3DDevice8.h"

CDirect3D8::CDirect3D8(IDirect3D9* d3d)
	: pDirect3D9(d3d)
{
	AdapterInformation.resize(pDirect3D9->GetAdapterCount());
	for (UINT i = 0; i < pDirect3D9->GetAdapterCount(); ++i)
	{
		for (UINT j = 0; j < Direct3D8CountD3DFormats; ++j)
		{
			AdapterInformation[i][j] = pDirect3D9->GetAdapterModeCount(i, Direct3D8AllowedD3DFormats[j]);
		}
	}
}

CDirect3D8::~CDirect3D8()
{
	pDirect3D9 = NULL;
}

HRESULT WINAPI CDirect3D8::QueryInterface(THIS_ REFIID riid, void** ppvObj)
{
	if (riid == IID_IUnknown
		|| riid == IID_IDirect3D8)
	{
		AddRef();
		*ppvObj = this;
		return D3D_OK;
	}

	*ppvObj = NULL;
	return E_NOINTERFACE;
}

ULONG WINAPI CDirect3D8::AddRef(THIS)
{
	return pDirect3D9->AddRef();
}

ULONG WINAPI CDirect3D8::Release(THIS)
{
	ULONG count = pDirect3D9->Release();
	if (0 == count)
	{
		delete this;
	}
	return count;
}

STDMETHODIMP CDirect3D8::RegisterSoftwareDevice(THIS_ void* pInitializeFunction)
{
	return pDirect3D9->RegisterSoftwareDevice(pInitializeFunction);
}

STDMETHODIMP_(UINT) CDirect3D8::GetAdapterCount(THIS)
{
	return pDirect3D9->GetAdapterCount();
}

STDMETHODIMP CDirect3D8::GetAdapterIdentifier(THIS_ UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER8* pIdentifier)
{
	D3DADAPTER_IDENTIFIER9 D3DIdentifier9;

	HRESULT result = pDirect3D9->GetAdapterIdentifier(Adapter, Flags, &D3DIdentifier9);

	strncpy_s(pIdentifier->Driver, MAX_DEVICE_IDENTIFIER_STRING, D3DIdentifier9.Driver, MAX_DEVICE_IDENTIFIER_STRING);
	strncpy_s(pIdentifier->Description, MAX_DEVICE_IDENTIFIER_STRING, D3DIdentifier9.Description, MAX_DEVICE_IDENTIFIER_STRING);

	pIdentifier->VendorId = D3DIdentifier9.VendorId;
	pIdentifier->DeviceId = D3DIdentifier9.DeviceId;
	pIdentifier->SubSysId = D3DIdentifier9.SubSysId;
	pIdentifier->Revision = D3DIdentifier9.Revision;

	memcpy(&pIdentifier->DeviceIdentifier, &D3DIdentifier9.DeviceIdentifier, sizeof(GUID));

	pIdentifier->WHQLLevel = D3DIdentifier9.WHQLLevel;

#ifdef _WIN32
	memcpy(&pIdentifier->DriverVersion, &D3DIdentifier9.DriverVersion, sizeof(LARGE_INTEGER));
#else
	pIdentifier->DriverVersionLowPart = pIdentifier9->DriverVersionLowPart;
	pIdentifier->DriverVersionHighPart = pIdentifier9->DriverVersionHighPart;
#endif

	return result;
}

STDMETHODIMP_(UINT) CDirect3D8::GetAdapterModeCount(THIS_ UINT Adapter)
{
	if (Adapter >= AdapterInformation.size())
	{
		return 0;
	}

	UINT result = 0;
	for (UINT i = 0; i <Direct3D8CountD3DFormats; ++i)
	{
		result += AdapterInformation[Adapter][i];
	}
	return result;
}

STDMETHODIMP CDirect3D8::EnumAdapterModes(THIS_ UINT Adapter, UINT Mode, D3DDISPLAYMODE* pMode)
{
	if (Adapter >= AdapterInformation.size())
	{
		return D3DERR_INVALIDCALL;
	}

	UINT offset = 0;
	for (UINT i = 0; i < Direct3D8CountD3DFormats; ++i)
	{
		if (Mode < offset + AdapterInformation[Adapter][i])
		{
			return pDirect3D9->EnumAdapterModes(Adapter, Direct3D8AllowedD3DFormats[i], Mode - offset, pMode);
		}
		offset += AdapterInformation[Adapter][i];
	}
	return D3DERR_INVALIDCALL;
}

STDMETHODIMP CDirect3D8::GetAdapterDisplayMode(THIS_ UINT Adapter, D3DDISPLAYMODE* pMode)
{
	return pDirect3D9->GetAdapterDisplayMode(Adapter, pMode);
}

STDMETHODIMP CDirect3D8::CheckDeviceType(THIS_ UINT Adapter, D3DDEVTYPE CheckType, D3DFORMAT DisplayFormat, D3DFORMAT BackBufferFormat, BOOL Windowed)
{
	return pDirect3D9->CheckDeviceType(Adapter, CheckType, DisplayFormat, BackBufferFormat, Windowed);
}

STDMETHODIMP CDirect3D8::CheckDeviceFormat(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat)
{
	return pDirect3D9->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
}

STDMETHODIMP CDirect3D8::CheckDeviceMultiSampleType(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType)
{
	return pDirect3D9->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, NULL);
}

STDMETHODIMP CDirect3D8::CheckDepthStencilMatch(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat)
{
	return pDirect3D9->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
}

STDMETHODIMP CDirect3D8::GetDeviceCaps(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS8* pCaps)
{
	D3DCAPS9 D3DCaps9;
	HRESULT result = pDirect3D9->GetDeviceCaps(Adapter, DeviceType, &D3DCaps9);
	memcpy(pCaps, &D3DCaps9, sizeof(D3DCAPS8));
	return result;
}

STDMETHODIMP_(HMONITOR) CDirect3D8::GetAdapterMonitor(THIS_ UINT Adapter)
{
	return pDirect3D9->GetAdapterMonitor(Adapter);
}

STDMETHODIMP   CDirect3D8::CreateDevice(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3D8PRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice8** ppReturnedDeviceInterface)
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

	IDirect3DDevice9* pReturnedDeviceInterface9 = NULL;
	HRESULT hr = pDirect3D9->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, &D3DPresentationParameters9, &pReturnedDeviceInterface9);
	if (SUCCEEDED(hr))
	{
		CDirect3DDevice8* D3DDevice = DevicePool.Create(pReturnedDeviceInterface9, this);
		D3DDevice->SetZBufferDiscarding((pPresentationParameters->Flags & D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL) != 0);
		*ppReturnedDeviceInterface = D3DDevice;
	}
	return hr;
}
