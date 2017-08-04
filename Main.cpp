#include "Main.h"
#include "Hooks.h"
#include "Util/Log.h"

//
// Initializes everything and starts up
// the update loop
//
void Main::Init(HINSTANCE dllHandle)
{
	m_dllHandle = dllHandle;
  Log::Init();

  m_pCameraManager = new CameraManager();
  Log::Write("m_pCameraManager 0x%X", m_pCameraManager);
  Log::Write("g_mainHandle 0x%X", g_mainHandle);

  Hooks::Init();

	m_exit = false;
	while (!m_exit)
		Update();
}

//
// Updates all objects
// TODO: Add boost clock for delta time
//
void Main::Update()
{
  m_pCameraManager->Update(0);
  Sleep(1);
}


Main::Main()
{ }

Main::~Main()
{
  Hooks::RemoveHooks();

	m_dllHandle = 0;
  delete m_pCameraManager;
}
