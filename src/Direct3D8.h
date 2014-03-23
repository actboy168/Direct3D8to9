#pragma once

#ifndef POINTER_64
#define POINTER_64 __ptr64
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <d3d9.h>
#include <d3d9types.h>
#include "Direct3D8to9.h"
#include "ObjectPool.h"

#include <array>
#include <cassert>
#include <vector>

class CDirect3DDevice8;

static const D3DFORMAT Direct3D8AllowedD3DFormats[] = { D3DFMT_A1R5G5B5, D3DFMT_A2R10G10B10, D3DFMT_A8R8G8B8, D3DFMT_R5G6B5, D3DFMT_X1R5G5B5, D3DFMT_X8R8G8B8 };
static const size_t    Direct3D8CountD3DFormats = _countof(Direct3D8AllowedD3DFormats);

class CDirect3D8 
	: public IDirect3D8
{
public:
	CDirect3D8(IDirect3D9* d3d);
	virtual ~CDirect3D8();

private:
	IDirect3D9* pDirect3D9;
	std::vector<std::array<UINT, Direct3D8CountD3DFormats>> AdapterInformation;

public:
	CObjectPool<CDirect3DDevice8> DevicePool;

public:
	 // IUnknown methods
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj)  ;
    STDMETHOD_(ULONG,AddRef)(THIS)  ;
    STDMETHOD_(ULONG,Release)(THIS)  ;

    // IDirect3D8 methods
    STDMETHOD(RegisterSoftwareDevice)(THIS_ void* pInitializeFunction)  ;
    STDMETHOD_(UINT, GetAdapterCount)(THIS)  ;
    STDMETHOD(GetAdapterIdentifier)(THIS_ UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER8* pIdentifier)  ;
    STDMETHOD_(UINT, GetAdapterModeCount)(THIS_ UINT Adapter)  ;
    STDMETHOD(EnumAdapterModes)(THIS_ UINT Adapter,UINT Mode,D3DDISPLAYMODE* pMode)  ;
    STDMETHOD(GetAdapterDisplayMode)(THIS_ UINT Adapter,D3DDISPLAYMODE* pMode)  ;
    STDMETHOD(CheckDeviceType)(THIS_ UINT Adapter,D3DDEVTYPE CheckType,D3DFORMAT DisplayFormat,D3DFORMAT BackBufferFormat,BOOL Windowed)  ;
    STDMETHOD(CheckDeviceFormat)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat)  ;
    STDMETHOD(CheckDeviceMultiSampleType)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType)  ;
    STDMETHOD(CheckDepthStencilMatch)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat)  ;
    STDMETHOD(GetDeviceCaps)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS8* pCaps)  ;
    STDMETHOD_(HMONITOR, GetAdapterMonitor)(THIS_ UINT Adapter)  ;
    STDMETHOD(CreateDevice)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3D8PRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice8** ppReturnedDeviceInterface)  ;
};
