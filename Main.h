#pragma once
#include <Windows.h>
#include <memory>

#include "Camera/CameraManager.h"

class Main
{
public:
  Main();
  ~Main();

	void Init(HINSTANCE);
	bool IsExiting() { return m_exit; }

  CameraManager* GetCameraManager() { return m_pCameraManager; }

private:
	void Update();

	HINSTANCE m_dllHandle;
	bool m_exit;

	CameraManager* m_pCameraManager;


public:
	Main(Main const&)			= delete;
	void operator=(Main const&) = delete;
};

static Main* g_mainHandle = 0;