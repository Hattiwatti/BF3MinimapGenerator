#include "CameraManager.h"
#include "../FB SDK/Frostbite.h"
#include "../Util/Log.h"
#include "../Util/Util.hpp"

CameraManager::CameraManager()
{
  Log::Write("Initializing Camera Manager");
  
  // Initialize freecamera structure with current ingame camera position
  // and point camera down
  fb::LinearTransform cameraTransform = fb::GameRenderer::Singleton()->m_viewParams.firstPersonTransform;
  
  m_camera.x = cameraTransform.trans.x;
  m_camera.y = cameraTransform.trans.y + 10;
  m_camera.z = cameraTransform.trans.z;
  m_camera.yaw = 0;
  m_camera.roll = 0;
  m_camera.pitch = XMConvertToRadians(-90.f);

  /* Testing */
  XMMATRIX freecamMatrix = XMMatrixRotationRollPitchYaw(m_camera.pitch, m_camera.yaw, m_camera.roll);
  freecamMatrix.r[3] = XMVectorSet(m_camera.x, m_camera.y, m_camera.z, 0);
  XMStoreFloat4x4(&m_camera.finalMatrix, freecamMatrix);
  m_cameraEnabled = false; 
  /* Testing */

  Log::Write("m_camera 0x%X", &m_camera);
  Log::Write("Camera Manager initialized");
}

CameraManager::~CameraManager()
{
  //
}

void CameraManager::Update(double dt)
{
  // Check if game is in focus
  if (!fb::DxRenderer::Singleton()->m_bFullscreenActive)
    return;

  if(GetAsyncKeyState(VK_INSERT) & 0x8000)
  {
    m_cameraEnabled = !m_cameraEnabled;

    // Patch to force 3rd person view
    // Stops game from reading byte that tells if the camera is
    // in first person view
    if(m_cameraEnabled)
      Util::WriteMemory(0x01065540, (const void*)(new BYTE[4]{ 0x90, 0x90, 0x90, 0x90 }), 4);
    else
      Util::WriteMemory(0x01065540, (const void*)(new BYTE[4]{ 0x8A, 0x44, 0x8A, 0x08 }), 4);

    while (GetAsyncKeyState(VK_INSERT) & 0x8000)
      Sleep(100);
  }

  // Toggle orthographic view
  if(GetAsyncKeyState(VK_DELETE) & 0x8000)
  {
    fb::GameRenderSettings* pSettings = fb::GameRenderer::Singleton()->getSettings();
    pSettings->m_ForceOrthoViewEnable = !pSettings->m_ForceOrthoViewEnable;
    pSettings->m_ForceSquareOrthoView = pSettings->m_ForceOrthoViewEnable;
    pSettings->m_ForceOrthoViewSize = 500.0f;

    while (GetAsyncKeyState(VK_DELETE) & 0x8000)
      Sleep(100);
  }

  if (!m_cameraEnabled) return;

  // Simple camera movement
  if(GetAsyncKeyState('W') & 0x8000)
  {
    m_camera.finalMatrix._41 += m_camera.finalMatrix._21 * 0.01;
    m_camera.finalMatrix._42 += m_camera.finalMatrix._22 * 0.01;
    m_camera.finalMatrix._43 += m_camera.finalMatrix._23 * 0.01;
  }
  if (GetAsyncKeyState('S') & 0x8000)
  {
    m_camera.finalMatrix._41 -= m_camera.finalMatrix._21 * 0.02;
    m_camera.finalMatrix._42 -= m_camera.finalMatrix._22 * 0.02;
    m_camera.finalMatrix._43 -= m_camera.finalMatrix._23 * 0.02;
  }
  if (GetAsyncKeyState('A') & 0x8000)
  {
    m_camera.finalMatrix._41 -= m_camera.finalMatrix._11 * 0.02;
    m_camera.finalMatrix._42 -= m_camera.finalMatrix._12 * 0.02;
    m_camera.finalMatrix._43 -= m_camera.finalMatrix._13 * 0.02;
  }
  if (GetAsyncKeyState('D') & 0x8000)
  {
    m_camera.finalMatrix._41 += m_camera.finalMatrix._11 * 0.02;
    m_camera.finalMatrix._42 += m_camera.finalMatrix._12 * 0.02;
    m_camera.finalMatrix._43 += m_camera.finalMatrix._13 * 0.02;
  }
  if(GetAsyncKeyState(VK_SPACE) & 0x8000)
  {
    m_camera.finalMatrix._41 += m_camera.finalMatrix._31 * 0.05;
    m_camera.finalMatrix._42 += m_camera.finalMatrix._32 * 0.05;
    m_camera.finalMatrix._43 += m_camera.finalMatrix._33 * 0.05;
  }
  if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
  {
    m_camera.finalMatrix._41 -= m_camera.finalMatrix._31 * 0.05;
    m_camera.finalMatrix._42 -= m_camera.finalMatrix._32 * 0.05;
    m_camera.finalMatrix._43 -= m_camera.finalMatrix._33 * 0.05;
  }
}

void CameraManager::CameraHook(int pMatrix)
{
  if (!m_cameraEnabled) return;

  XMMATRIX* pCameraMatrix = (XMMATRIX*)pMatrix;
  *pCameraMatrix = XMLoadFloat4x4(&m_camera.finalMatrix);
}


