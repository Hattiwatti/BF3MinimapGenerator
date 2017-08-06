#include "UserInterface.h"
#include "ImGui/imgui_impl_dx11.h"
#include "FB SDK/Frostbite.h"
#include "Util/Log.h"
#include "Main.h"

#include <algorithm>
#include <winuser.h>

UserInterface::UserInterface()
{
  m_initialized = false;
  fb::DxRenderer* pDxRenderer = fb::DxRenderer::Singleton();

  if(!ImGui_ImplDX11_Init((void*)pDxRenderer->m_hWnd, pDxRenderer->pDevice, pDxRenderer->pContext))
  {
    Log::Error("Failed to initialize ImGui DX11 handler. GetLastError 0x%X", GetLastError());
    return;
  }

  // Find by class name, should be unique and stay the same
  // If not found, use window title
  DWORD thread_id = GetWindowThreadProcessId(FindWindowA("Battlefield 3", NULL), NULL);
  if(!thread_id)
    thread_id = GetWindowThreadProcessId(FindWindowA(NULL, "Battlefield 3™"), NULL);

  if (thread_id)
  {
    if (!(hGetMessage = SetWindowsHookEx(WH_GETMESSAGE, this->GetMessage_Callback, g_mainHandle->GetDllHandle(), thread_id)))
      Log::Write("Couldn't create WH_GETMESSAGE hook. LastError 0x%X", GetLastError());
  }
  else Log::Warning("Could not find window thread handle");

  m_enabled = false;
  m_hasKeyboardFocus = false;
  m_hasMouseFocus = false;

  ImGuiStyle& Style = ImGui::GetStyle();
  Style.WindowRounding = 0.0f;
  Style.ChildWindowRounding = 0.0f;
  Style.Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
  Style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);

  m_initialized = true;
}

UserInterface::~UserInterface()
{
  m_enabled = m_initialized = false;
  ImGui_ImplDX11_InvalidateDeviceObjects();
  ImGui_ImplDX11_Shutdown();
}

XMVECTOR click_World;
XMVECTOR drag_World;
bool dragged = false;

void UserInterface::Draw()
{
  if (!m_enabled || !m_initialized) return;

  ImGui_ImplDX11_NewFrame();
  {
    ImGui::SetNextWindowSize(ImVec2(300, 500));
    ImGui::Begin("Minimap Generator", nullptr);
    {
      ImGui::InputFloat("Camera Speed", &g_mainHandle->GetCameraManager()->GetCamera()->movementSpeed, 1, 0, 2);
      ImGui::InputFloat("Camera Height", &g_mainHandle->GetCameraManager()->GetCamera()->finalMatrix._42, 5, 0, 0);
      ImGui::InputFloat("OrthoView Size", &fb::GameRenderer::Singleton()->getSettings()->m_ForceOrthoViewSize, 1, 2, 0);
      ImGui::InputFloat("Resolution", &g_mainHandle->GetOrthoSize(), 1, 2, 0);

      ImGui::Checkbox("Disable fog", &g_mainHandle->GetVisualOverrides().disableFog);

      ImGui::Text("Click screen-to-world");
      ImGui::Text("X: %.2f", click_World.m128_f32[0]);
      ImGui::Text("Y: %.2f", click_World.m128_f32[1]);
      ImGui::Text("Drag screen-to-world");
      ImGui::Text("X: %.2f", drag_World.m128_f32[0]);
      ImGui::Text("Y: %.2f", drag_World.m128_f32[1]);

      if(ImGui::Button("Generate minimap", ImVec2(120,30)))
      {
        g_mainHandle->Start(XMFLOAT2(click_World.m128_f32[0], click_World.m128_f32[1]),
                                      XMFLOAT2(drag_World.m128_f32[0], drag_World.m128_f32[1]));
      }
    } ImGui::End();
  }

  ImGui::Render();

  m_hasKeyboardFocus = ImGui::GetIO().WantCaptureKeyboard;
  m_hasMouseFocus = ImGui::GetIO().WantCaptureMouse;

  if(!m_hasMouseFocus && ImGui::IsMouseDragging(0))
  {
    fb::GameRenderer* pGameRenderer = fb::GameRenderer::Singleton();
    fb::DxRenderer* pDxRenderer = fb::DxRenderer::Singleton();

    ImVec2 clickPos = ImGui::GetIO().MouseClickedPos[0];
    ImVec2 dragDelta = ImGui::GetMouseDragDelta(0);

    // Convert dragged area to world space and round to closest
    // fitting square for given resolution
    //
    // Example:
    // User draws a square that is 1000x1000 units in world space
    // and user has set resolution to 400. 1000/400 = 2.5 which
    // gets rounded to 3, so the resulting closest square is 3x3
    // or 1200x1200. Convert this back to screen space and display.

    // Square side length in screen space
    float sideLength = std::max(fabs(dragDelta.x), fabs(dragDelta.y));

    // Unit-to-pixel ratio
    float widthRatio = (pGameRenderer->m_viewParams.view.m_desc.orthoWidth) / (float)pDxRenderer->m_screenInfo.m_nWidth;
    float heightRatio = (pGameRenderer->m_viewParams.view.m_desc.orthoHeight) / (float)pDxRenderer->m_screenInfo.m_nHeight;

    // Convert to world space
    float sideLength_World = sideLength * widthRatio;

    // How many grids fit? Round to closest
    float gridSize = sideLength_World / g_mainHandle->GetOrthoSize();
    gridSize = round(gridSize);

    // Back to screen space
    sideLength_World = gridSize*g_mainHandle->GetOrthoSize();
    sideLength = sideLength_World / widthRatio;


    XMFLOAT2 square = XMFLOAT2(dragDelta.x < 0 ? -sideLength : sideLength,
                                dragDelta.y < 0 ? -sideLength : sideLength);

    XMFLOAT2 dragCorner(clickPos.x + square.x, clickPos.y + square.y);

    // Draw capture area
    fb::DebugRenderer2::Singleton()->drawRect2d(new fb::Tuple2<float>(clickPos.x, clickPos.y),
        new fb::Tuple2<float>(dragCorner.x, dragCorner.y),
        fb::Color32(0xFF,0,0,0xB0));

    // Draw grid to visualize cells
    for(int i = 0; i <= gridSize; ++i)
    {
      fb::DebugRenderer2::Singleton()->drawLine2d(new fb::Tuple2<float>(clickPos.x + i*(sideLength / gridSize)*(dragDelta.x < 0 ? -1 : 1), clickPos.y),
        new fb::Tuple2<float>(clickPos.x + i*(sideLength / gridSize)*(dragDelta.x < 0 ? -1:1), dragCorner.y),
        fb::Color32(0, 0, 0, 0xFF));
    }
    for (int i = 0; i <= gridSize; ++i)
    {
      fb::DebugRenderer2::Singleton()->drawLine2d(new fb::Tuple2<float>(clickPos.x, clickPos.y + i*(sideLength / gridSize)*(dragDelta.y < 0 ? -1 : 1)),
        new fb::Tuple2<float>(dragCorner.x, clickPos.y + i*(sideLength / gridSize)*(dragDelta.y < 0 ? -1 : 1)),
        fb::Color32(0, 0, 0, 0xFF));
    }


    if (pGameRenderer->m_viewParams.view.m_desc.type == 0)
    {
      if (pGameRenderer->m_viewParams.view.Update())
      {
        pGameRenderer->ScreenToWorld(XMFLOAT2(clickPos.x, clickPos.y), click_World);
        pGameRenderer->ScreenToWorld(XMFLOAT2(clickPos.x + square.x, clickPos.y + square.y), drag_World);
      }
    }
    else
    {
      XMFLOAT2 center((float)pDxRenderer->m_screenInfo.m_nWidth / 2, (float)pDxRenderer->m_screenInfo.m_nHeight / 2);

      XMFLOAT4 eyeTrans = (XMFLOAT4&)pGameRenderer->m_viewParams.firstPersonTransform.trans;

      click_World = XMVectorSet(eyeTrans.x + (clickPos.x - center.x)*widthRatio, eyeTrans.z + (clickPos.y - center.y)*heightRatio, 0, 0);
      drag_World = XMVectorSet(eyeTrans.x + (dragCorner.x - center.x)*widthRatio, eyeTrans.z + (dragCorner.y - center.y)*heightRatio, 0, 0);
      
      dragged = true;
    }
  }

}

void UserInterface::Toggle()
{
  m_enabled = !m_enabled;
  fb::BorderInputNode::Singleton()->m_mouse->enableCursorMode(m_enabled, 1);
  fb::BorderInputNode::Singleton()->m_mouse->setUIOwnsInput(m_enabled);
}

extern LRESULT ImGui_ImplDX11_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall UserInterface::GetMessage_Callback(int nCode, WPARAM wParam, LPARAM lParam)
{
  if (fb::DxRenderer::Singleton()->m_bFullscreenActive)
  {
    MSG* pMsg = (MSG*)lParam;
    if (!ImGui_ImplDX11_WndProcHandler(pMsg->hwnd, pMsg->message, pMsg->wParam, pMsg->lParam))
    {
      if (pMsg->message == WM_SIZE)
      {

      }
    }
  }

  return CallNextHookEx(g_mainHandle->GetUI()->GetMessageHook(), nCode, wParam, lParam);
}