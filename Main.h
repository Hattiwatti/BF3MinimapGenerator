#pragma once
#include <Windows.h>
#include <memory>

#include "Camera/CameraManager.h"

class Main
{
public:
	void Init(HINSTANCE);
	bool IsExiting() { return m_exit; }

private:
	void Update();

	HINSTANCE m_dllHandle;
	bool m_exit;

	std::unique_ptr<CameraManager> m_pCameraManager;


public:
	Main();
	~Main();

	Main(Main const&)			= delete;
	void operator=(Main const&) = delete;
};

static Main* g_mainHandle = 0;