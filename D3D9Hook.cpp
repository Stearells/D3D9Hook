#include "D3D9Hook.h"
#include <memory>

void* pOrig;
void* pHooked;

D3D9Hook::fun Renderer;
D3D9Hook::fun poES9;

bool initFlag = false;

void D3D9Hook::InstallHook(fun pRender)
{
	if (initFlag)
		return;

	pOrig = malloc(5);
	pHooked = malloc(5);

	Renderer = pRender;

	GetMethods();
	HookMethods();
}

void D3D9Hook::GetMethods(void)
{
	HANDLE hD3D9 = GetModuleHandle(L"d3d9.dll");
	poES9 = (D3D9Hook::fun)((DWORD)hD3D9 + 0x2279F);
}

void D3D9Hook::HookMethods(void)
{
	DWORD addr = (DWORD)reinterpret_cast<D3D9Hook::fun>(&hES9) - (DWORD)poES9 - 5;

	DWORD dwback;
	VirtualProtect(poES9, 5, PAGE_EXECUTE_READWRITE, &dwback);

	memcpy(pOrig, poES9, 5);

	Memory::Write<BYTE>((DWORD)poES9, 0xE9);
	Memory::Write<DWORD>((DWORD)poES9 + 1, addr);

	memcpy(pHooked, poES9, 5);
}

void D3D9Hook::hES9(IDirect3DDevice9* device)
{
	memcpy(poES9, pOrig, 5);
	__asm	push device
	__asm	call [poES9]
	Renderer(device);
	memcpy(poES9, pHooked, 5);
}