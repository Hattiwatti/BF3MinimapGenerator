#pragma once
#include "../Frostbite.h"

struct GamepadState
{
  XMFLOAT2 leftStick;
  XMFLOAT2 rightStick;
  double trigger;
  BYTE LeftShoulder;
  BYTE RightShoulder;
  BYTE LeftThumbButton;
  BYTE RightThumbButton;
  BYTE DPad_Left;
  BYTE DPad_Right;
  BYTE DPad_Up;
  BYTE DPad_Down;
  BYTE Buttons[4];
};

struct ControlState
{
  float dX, dY, dZ;
  float dPitch, dYaw, dRoll;
};

struct Camera
{
  float x, y, z;
  float pitch, yaw, roll;

  float movementSpeed{ 1.0f };
  float rotationSpeed{ 1.0f };
  float rollSpeed{ 0.2f };

  XMMATRIX finalMatrix{ XMMatrixIdentity() };
};