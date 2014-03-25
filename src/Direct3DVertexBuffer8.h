#pragma once

#include "Direct3D8.h"

class CDirect3DVertexBuffer8
	: public IDirect3DVertexBuffer8
{
public:
	CDirect3DVertexBuffer8(IDirect3DVertexBuffer9* vertexbuffer, CDirect3DDevice8* device);
	~CDirect3DVertexBuffer8();


private:
	IDirect3DVertexBuffer9* pVertexBuffer9;
	CDirect3DDevice8* pDevice8;

public:
	IDirect3DVertexBuffer9* ToNine() const { return (!this) ? nullptr: pVertexBuffer9; }

public:
	// IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj);
	STDMETHOD_(ULONG, AddRef)(THIS);
	STDMETHOD_(ULONG, Release)(THIS);

public:
	// IDirect3DVertexBuffer8 Methods
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice);
	STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags);
	STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData);
	STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid);
	STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew);
	STDMETHOD_(DWORD, GetPriority)(THIS);
	STDMETHOD_(void, PreLoad)(THIS);
	STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS);
	STDMETHOD(Lock)(THIS_ UINT OffsetToLock, UINT SizeToLock, BYTE** ppbData, DWORD Flags);
	STDMETHOD(Unlock)(THIS);
	STDMETHOD(GetDesc)(THIS_ D3DVERTEXBUFFER_DESC *pDesc);
};
