#include "Main.h"
#include "Hooks.h"

void Main::Init(HINSTANCE dllHandle)
{
	m_dllHandle = dllHandle;

	m_pCameraManager = std::make_unique<CameraManager>();

  Hooks::Init();

	m_exit = false;
	while (!m_exit)
		Update();
}

Main::Main()
{ }

Main::~Main()
{
  Hooks::RemoveHooks();

	m_dllHandle = 0;
  delete m_pCameraManager.release();
}
