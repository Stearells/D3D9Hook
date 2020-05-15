D3D9Hook - Simple hook for Direct3D 9.
====

You can use in here:
```CPP
/* dllmain.h */

#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "Hook/D3D9Hook.h"
#include <iostream>

#pragma comment(lib, "Hook/D3D9Hook_d.lib")
```

```CPP
/* dllmain.cpp */

#include "dllmain.h"

void HookedES9(IDirect3DDevice9* device)
{
    std::cout << "Hooked!" << std::endl;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        AllocConsole();
        std::freopen("CONOUT$", "w", stdout);

        D3D9Hook::InstallHook(D3D9Hook::fun(&HookedES9));
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        //D3D9Hook::FreeHook(); //unstable feature.
        break;
    }
    return TRUE;
}
```
