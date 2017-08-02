#pragma once
#include <Windows.h>

class Hooks
{
public:
  static void Init();

  static void DisableHooks();
  static void RemoveHooks();

private:
  static void CreateHook(const char*, int, PVOID, LPVOID*);
  static void RemoveHook(PVOID);
  static PBYTE WINAPI HookVTableFunction(PDWORD*, PBYTE, SIZE_T);
};