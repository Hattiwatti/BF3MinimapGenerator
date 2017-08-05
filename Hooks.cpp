#include "Hooks.h"
#include "Main.h"
#include "FB SDK/Frostbite.h"
#include "Util/Log.h"

#include "MinHook.h"
#pragma comment(lib, "libMinHook.x86.lib")

typedef HRESULT(WINAPI * tD3D11Present)(IDXGISwapChain*, UINT, UINT);
typedef void(__stdcall* tCameraUpdate)(int,int,int,int);

tD3D11Present oD3D11Present = nullptr;
tCameraUpdate oCameraUpdate = nullptr;

HRESULT WINAPI hD3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
  g_mainHandle->GetUI()->Draw();
  return oD3D11Present(pSwapChain, SyncInterval, Flags);
}


__declspec(naked) void hCameraUpdateAsm(int a1, int a2)
{
  __asm
  {
    push ecx // save ecx
    push ebp // save ebp
    mov ebp, esp // save esp
    sub esp, __LOCAL_SIZE // allocate space for local variable
  }

  int pMatrix;
  pMatrix = a2;
  g_mainHandle->GetCameraManager()->CameraHook(pMatrix);

  __asm
  {
    mov esp, ebp // restore esp
    pop ebp // restore ebp
    pop ecx // restore ecx
    jmp oCameraUpdate // jump to original
  }
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
  (*ppVTable)[iIndex] = (DWORD)pHook;

  VirtualProtect((void*)((*ppVTable) + iIndex), sizeof(PDWORD), dwOld, &dwOld);

  return pOrig;
}

void Hooks::Init()
{
  MH_STATUS status = MH_Initialize();
  if (status != MH_OK)
  {
    Log::Error("Could not initialize MinHook, error code: 0x%X", status);
    return;
  }

  CreateHook("Camera Update", 0x11A4560, hCameraUpdateAsm, (LPVOID*)&oCameraUpdate);
  oD3D11Present = (tD3D11Present)HookVTableFunction((PDWORD*)fb::DxRenderer::Singleton()->pSwapChain, (PBYTE)hD3D11Present, 8);
}

void Hooks::RemoveHooks()
{
  MH_RemoveHook(MH_ALL_HOOKS);
  MH_Uninitialize();
}