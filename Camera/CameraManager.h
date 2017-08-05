#pragma once
#include "CameraHelpers.h"

class CameraManager
{
public:
  void CameraHook(int pMatrix);
  void Update(double);

  void ToggleCamera();
  Camera* GetCamera() { return &m_camera; }

private:
  bool m_cameraEnabled;

  Camera m_camera;
  ControlState m_controlState;

public:
	CameraManager();
	~CameraManager();

	CameraManager(const CameraManager&)   = delete;
	void operator=(const CameraManager&)  = delete;
};