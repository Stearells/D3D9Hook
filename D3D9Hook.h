/*
* Simple D3D9 Hook v1.1
* Stearells (C) 2020
* \(o_o)/
*/

#pragma once

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace D3D9Hook
{
	typedef void (*fun)(IDirect3DDevice9* device);

	void InstallHook(fun pRender);
	void GetMethods(void);
	void HookMethods(void);
	void hES9(IDirect3DDevice9* device);
	void FreeHook(void);
}

namespace Memory
{
	template <typename T>
	void Write(DWORD addr, T value)
	{
		*(T*)addr = value;
	}

	template <typename T>
	T Read(DWORD addr)
	{
		return *(T*)addr;
	}
}