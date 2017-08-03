#include "Log.h"
#include <stdio.h>

HANDLE Log::hstdin, Log::hstdout;
FILE* Log::pfstdin;
FILE* Log::pfstdout;

void Log::Init()
{
  AllocConsole();
  freopen_s(&pfstdout, "CONOUT$", "w", stdout);
  freopen_s(&pfstdin, "CONIN$", "r", stdin);
  //freopen("CONOUT$", "w", stdout);
  //freopen("CONIN$", "r", stdin);
  hstdin = GetStdHandle(STD_INPUT_HANDLE);
  hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Log::Write(const char* format, ...)
{
  va_list args;
  //ptime now = second_clock::local_time();
  //string timeStamp = to_simple_string(now) + "  ";
  //SetConsoleTextAttribute(hstdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
  //printf(timeStamp.c_str());
  SetConsoleTextAttribute(hstdout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
  va_start(args, format);
  vfprintf(stdout, format, args);
  va_end(args);
  fprintf(stdout, "\n");
}

void Log::Warning(const char* format, ...)
{
  va_list args;
  //ptime now = second_clock::local_time();
  //string timeStamp = to_simple_string(now) + "  ";
  //SetConsoleTextAttribute(hstdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
  //printf(timeStamp.c_str());
  SetConsoleTextAttribute(hstdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
  va_start(args, format);
  vfprintf(stdout, format, args);
  va_end(args);
  fprintf(stdout, "\n");
}

void Log::Error(const char* format, ...)
{
  va_list args;
  //ptime now = second_clock::local_time();
  //string timeStamp = to_simple_string(now) + "  ";
  //SetConsoleTextAttribute(hstdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
  //printf(timeStamp.c_str());
  SetConsoleTextAttribute(hstdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
  va_start(args, format);
  vfprintf(stdout, format, args);
  va_end(args);
  fprintf(stdout, "\n");
}

void Log::Ok(const char* format, ...)
{
  va_list args;
  //ptime now = second_clock::local_time();
  //string timeStamp = to_simple_string(now) + "  ";
  //SetConsoleTextAttribute(hstdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
  //printf(timeStamp.c_str());
  SetConsoleTextAttribute(hstdout, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
  va_start(args, format);
  vfprintf(stdout, format, args);
  va_end(args);
  fprintf(stdout, "\n");
}