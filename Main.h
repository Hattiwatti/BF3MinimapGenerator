#pragma once
#include <Windows.h>
#include <memory>
#include <vector>

#include <DirectXTex.h>

#include "Camera/CameraManager.h"
#include "UserInterface.h"

class Main
{
public:
  Main();
  ~Main();

	void Init(HINSTANCE);
	bool IsExiting() { return m_exit; }

  CameraManager* GetCameraManager() { return m_pCameraManager; }
  UserInterface* GetUI() { return m_pUserInterface; }
  HINSTANCE GetDllHandle() { return m_dllHandle; }

  float& GetOrthoSize() { return m_orthoSize; }

  void Start(DirectX::XMFLOAT2, DirectX::XMFLOAT2);
  void GenerateMinimap(DirectX::XMFLOAT2, DirectX::XMFLOAT2);
  void Capture();

private:
	void Update();

	HINSTANCE m_dllHandle;
	bool m_exit;

	CameraManager* m_pCameraManager;
  UserInterface* m_pUserInterface;

  bool m_startGenerating;
  DirectX::XMFLOAT2 _corner1;
  DirectX::XMFLOAT2 _corner2;

  bool m_requestCapture;
  int m_currentRow;
  int m_currentColumn;

  float m_orthoSize;

public:
	Main(Main const&)			= delete;
	void operator=(Main const&) = delete;
};

extern Main* g_mainHandle;