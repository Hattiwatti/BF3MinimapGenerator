#pragma once
#include <Windows.h>

namespace Util
{
  inline BOOL WriteMemory(DWORD_PTR dwAddress, const void* cpvPatch, DWORD dwSize)
  {
    DWORD dwProtect;
    if (VirtualProtect((void*)dwAddress, dwSize, PAGE_READWRITE, &dwProtect)) //Unprotect the memory
      memcpy((void*)dwAddress, cpvPatch, dwSize); //Write our patch
    else

      return false; //Failed to unprotect, so return false..
    return VirtualProtect((void*)dwAddress, dwSize, dwProtect, new DWORD); //Reprotect the memory
  }
}