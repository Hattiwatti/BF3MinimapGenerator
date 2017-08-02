#pragma once
#include <Windows.h>

class Log
{
public:
  static void Init();

  static void Write(const char* format, ...);
  static void Warning(const char* format, ...);
  static void Error(const char* format, ...);
  static void Ok(const char* format, ...);

private:
  static HANDLE hstdin;
  static HANDLE hstdout;
};