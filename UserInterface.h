#pragma once
#include <Windows.h>

class UserInterface
{
public:
  void Toggle();
  void Draw();

  bool IsEnabled() { return m_enabled; }
  bool IsInitialized() { return m_initialized; }
  bool HasKeyboardFocus() { return m_hasKeyboardFocus; }
  bool HasMouseFocus() { return m_hasMouseFocus; }

  HHOOK GetMessageHook() { return hGetMessage; }

private:
  bool m_enabled;
  bool m_hasKeyboardFocus;
  bool m_hasMouseFocus;

  HHOOK hGetMessage;
  static LRESULT __stdcall GetMessage_Callback(int nCode, WPARAM wParam, LPARAM lParam);

  bool m_initialized;

public:
  UserInterface();
  ~UserInterface();

  UserInterface(UserInterface const&) = delete;
  void operator=(UserInterface const&) = delete;
};