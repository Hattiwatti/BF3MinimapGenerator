#pragma once

#include <windows.h>
#include <DXGI.h>
#include <D3D11.h>
#include <DirectXMath.h>

using namespace DirectX;

namespace fb
{
  class ClientGameContext
  {
  public:
    BYTE Pad000[0xC];
    int m_gameTime;
    int m_level;
    BYTE Pad014[0x1C];
    int m_playerManager;
    BYTE Pad034[0x4];
    int m_clientGameView;

  public:
    static ClientGameContext* GetInstance()
    {
      return *(ClientGameContext**)0x123;
    }
  };
}