#include <Windows.h>
#include "Main.h"

// Gets called when the DLL is injected
// Creates Main class and passes the DLL Instance handle
DWORD WINAPI Initialize(LPVOID arg)
{
	g_mainHandle = new Main();
  HINSTANCE* pDllInstance = static_cast<HINSTANCE*>(arg);

	g_mainHandle->Init(*pDllInstance);

  delete pDllInstance;
  delete g_mainHandle;
  g_mainHandle = 0;
	return 0;
}

// DLL entry point
DWORD WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if(dwReason == DLL_PROCESS_ATTACH)
		CreateThread(0, 0, &Initialize, new HINSTANCE(hInstance), 0, 0);

	return 1;
}