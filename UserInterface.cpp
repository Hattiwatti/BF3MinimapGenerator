#include "UserInterface.h"
#include "ImGui/imgui_impl_dx11.h"
#include "FB SDK/Frostbite.h"
#include "Util/Log.h"
#include "Main.h"

#include <algorithm>

UserInterface::UserInterface()
{
  m_initialized = false;
  fb::DxRenderer* pDxRenderer = fb::DxRenderer::Singleton();

  if(!ImGui_ImplDX11_Init((void*)pDxRenderer->m_hWnd, pDxRenderer->pDevice, pDxRenderer->pContext))
  {
    Log::Error("Failed to initialize ImGui DX11 handler. GetLastError 0x%X", GetLastError());
    return;
  }

  DWORD thread_id = GetWindowThreadProcessId(FindWindowA(NULL, "Battlefield 3 - Venice Unleashed [Beta Build 11182]"), NULL);
  if (!(hGetMessage = SetWindowsHookEx(WH_GETMESSAGE, this->GetMessage_Callback, g_mainHandle->GetDllHandle(), thread_id)))
    Log::Write("Couldn't create WH_GETMESSAGE hook. LastError 0x%X", GetLastError());

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

XMVECTOR click_World;
XMVECTOR drag_World;
bool dragged = false;

void UserInterface::Draw()
{
  if (!m_enabled || !m_initialized) return;

  ImGui_ImplDX11_NewFrame();
  {
    ImGuiIO& io = ImGui::GetIO();

    ImGui::SetNextWindowSize(ImVec2(300, 500));
    ImGui::Begin("Minimap Generator", nullptr);
    {
      ImGui::InputFloat("Camera Speed", &g_mainHandle->GetCameraManager()->GetCamera()->movementSpeed, 1, 0, 2);
      ImGui::InputFloat("Camera Height", &g_mainHandle->GetCameraManager()->GetCamera()->finalMatrix._42, 5, 0, 0);
      ImGui::InputFloat("OrthoView Size", &fb::GameRenderer::Singleton()->getSettings()->m_ForceOrthoViewSize, 1, 2, 0);
      ImGui::InputFloat("Resolution", g_mainHandle->GetOrthoSize(), 1, 2, 0);

      ImGui::Text("Click screen-to-world");
      ImGui::Text("X: %.2f", click_World.m128_f32[0]);
      ImGui::Text("Y: %.2f", click_World.m128_f32[1]);
      ImGui::Text("Drag screen-to-world");
      ImGui::Text("X: %.2f", drag_World.m128_f32[0]);
      ImGui::Text("Y: %.2f", drag_World.m128_f32[1]);
      if(ImGui::Button("Generate minimap", ImVec2(100,33)))
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

    float sideLength = std::max(fabs(dragDelta.x), fabs(dragDelta.y));
    XMFLOAT2 square = XMFLOAT2(dragDelta.x < 0 ? -sideLength : sideLength,
                                dragDelta.y < 0 ? -sideLength : sideLength);

    XMFLOAT2 dragCorner(clickPos.x + square.x, clickPos.y + square.y);
    fb::DebugRenderer2::Singleton()->drawRect2d(new fb::Tuple2<float>(clickPos.x, clickPos.y),
        new fb::Tuple2<float>(dragCorner.x, dragCorner.y),
        fb::Color32(0xFF,0,0,0xB0));

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
      float widthRatio = (pGameRenderer->m_viewParams.view.m_desc.orthoWidth) / (float)pDxRenderer->m_screenInfo.m_nWidth;
      float heightRatio = (pGameRenderer->m_viewParams.view.m_desc.orthoHeight) / (float)pDxRenderer->m_screenInfo.m_nHeight;
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