#include "Hooks.h"
#include "FB SDK/Frostbite.h"

#include "MinHook.h"
#pragma comment(lib, "libMinHook.x86.lib")

typedef HRESULT(WINAPI * tD3D11Present)(IDXGISwapChain*, UINT, UINT);
typedef void(__fastcall* tCameraUpdate)(int,int,int);

tD3D11Present oD3D11Present = nullptr;
tCameraUpdate oCameraUpdate = nullptr;

HRESULT WINAPI hD3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
  return oD3D11Present(pSwapChain, SyncInterval, Flags);
}

void __fastcall hCameraUpdate(int pCamera, int a2, int pMatrix)
{
  return oCameraUpdate(pCamera, a2, pMatrix);
}

//
// Creates a normal hook with MinHook and enables it
//
void Hooks::CreateHook(const char* name, int target, PVOID hook, LPVOID* original)
{
  if (MH_CreateHook((LPVOID)target, hook, original) != MH_OK)
  {
    //Log::Error("Could not create %s hook", name.c_str());
    return;
  }
  if (MH_EnableHook((LPVOID)target) != MH_OK)
  {
    //Log::Error("Could not enable %s hook", name.c_str());
    return;
  }

  //m_hooks.insert(std::pair<string, LPVOID>(name, (LPVOID)target));
}

//
// Hooks a function by changing the address at given index
// in the virtual function table
//
PBYTE WINAPI Hooks::HookVTableFunction(PDWORD* ppVTable, PBYTE pHook, SIZE_T iIndex) 
{
  DWORD dwOld = 0;
  VirtualProtect((void*)((*ppVTable) + iIndex), sizeof(PDWORD), PAGE_EXECUTE_READWRITE, &dwOld);

  PBYTE pOrig = ((PBYTE)(*ppVTable)[iIndex]);
  (*ppVTable)[iIndex] = (DWORD64)pHook;

  VirtualProtect((void*)((*ppVTable) + iIndex), sizeof(PDWORD), dwOld, &dwOld);

  return pOrig;
}

void Hooks::Init()
{
  if (MH_Initialize() != MH_OK)
    return;

  CreateHook("Camera Update", 0x11A4560, hCameraUpdate, (LPVOID*)&oCameraUpdate);

  oD3D11Present = (tD3D11Present)HookVTableFunction((PDWORD*)fb::DxRenderer::Singleton()->pSwapChain, (PBYTE)oD3D11Present, 8);
}