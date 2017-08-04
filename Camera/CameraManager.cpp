#include "CameraManager.h"
#include "../FB SDK/Frostbite.h"
#include "../Util/Log.h"

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
  if(GetAsyncKeyState(VK_INSERT) & 0x8000)
  {
    m_cameraEnabled = !m_cameraEnabled;

    while (GetAsyncKeyState(VK_INSERT) & 0x8000)
      Sleep(100);
  }

  if (!m_cameraEnabled) return;

  // Just testing camera movement
  if(GetAsyncKeyState('W') & 0x8000)
  {
    m_camera.finalMatrix._41 += m_camera.finalMatrix._21 * 0.001;
    m_camera.finalMatrix._42 += m_camera.finalMatrix._22 * 0.001;
    m_camera.finalMatrix._43 += m_camera.finalMatrix._23 * 0.001;
  }
}

void CameraManager::CameraHook(int pMatrix)
{
  if (!m_cameraEnabled) return;

  XMMATRIX* pCameraMatrix = (XMMATRIX*)pMatrix;
  *pCameraMatrix = XMLoadFloat4x4(&m_camera.finalMatrix);
}


