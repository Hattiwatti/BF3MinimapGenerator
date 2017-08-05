#include "Main.h"
#include "Hooks.h"
#include "Util/Log.h"
#include "FB SDK/Frostbite.h"

#include <wincodec.h>
#include <string>
#pragma comment(lib, "DirectXTex.lib")

//const float ORTHO_SIZE = 500.f;

//
// Initializes everything and starts up
// the update loop
//
void Main::Init(HINSTANCE dllHandle)
{
	m_dllHandle = dllHandle;
  Log::Init();

  m_exit = m_requestCapture = m_startGenerating = false;

  // Initialize Windows Runtime and COM for DirectXTex
  HRESULT hr = CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
  if(hr != S_OK)
    Log::Warning("CoInitialize failed. Result 0x%X", hr);

  m_pCameraManager = new CameraManager();
  m_pUserInterface = new UserInterface();

  Hooks::Init();

  fb::ClientLevel* pLevel = fb::ClientGameContext::Singleton()->m_level;
  fb::WorldRenderSettings* pRenderSettings = pLevel->m_worldRenderModule->m_worldRenderer->m_worldRenderSettings;
  pRenderSettings->m_shadowmapResolution = 4096;
  pLevel->m_vegetationManager->m_settings->m_maxActiveDistance = 4000;
  pLevel->m_vegetationManager->m_settings->m_shadowMeshEnable = 1;

  m_orthoSize = 500.0f;
	while (!m_exit)
		Update();
}

//
// Updates all objects
// TODO: Add boost clock for delta time (not really needed tho)
//
void Main::Update()
{
  if(GetAsyncKeyState(VK_F1) & 0x8000)
  {
    m_pUserInterface->Toggle();
    while (GetAsyncKeyState(VK_F1) & 0x8000)
      Sleep(100);
  }

  if(m_startGenerating)
    GenerateMinimap(_corner1, _corner2);

  m_pCameraManager->Update(0);
  Sleep(1);
}

//
// Function which the UI can call
// to begin minimap generation
//
void Main::Start(XMFLOAT2 corner1, XMFLOAT2 corner2)
{
  Log::Write("Requested to start generating minimap");
  if (m_startGenerating) return;

  _corner1 = corner1;
  _corner2 = corner2;
  m_startGenerating = true;
}

//
// Generates minimap images by dividing selected area
// to a grid of 500x500 cells (best fit) and saves them
// to files.
//
void Main::GenerateMinimap(XMFLOAT2 corner1, XMFLOAT2 corner2)
{
  Log::Write("Begin generating");
  fb::GameRenderer::Singleton()->getSettings()->m_ForceOrthoViewSize = m_orthoSize;
  fb::GameTimeSettings::Singleton()->m_timeScale = 0.01;

  // These calculations are probably obsolete since the UI already
  // calculates best fitting square

  Log::Write("corner1 %f : %f", corner1.x, corner1.y);
  Log::Write("corner2 %f : %f", corner2.x, corner2.y);
  XMFLOAT2 square(corner2.x - corner1.x, corner2.y - corner1.y);
  Log::Write("square %f : %f", square.x, square.y);
  float sizeAbs = fabs(square.x);

  Log::Write("Absolute size %fx%f", sizeAbs, sizeAbs);

  float gridAmount = round(sizeAbs / m_orthoSize);
  Log::Write("GridAmount %f", gridAmount);

  XMFLOAT2 center(corner2.x - (square.x / 2), corner2.y - (square.y / 2));
  Log::Write("Center or the square %f : %f", center.x, center.y);
  XMFLOAT2 startCell = center;

  int roundedDiv = (int)(gridAmount / 2);
  Log::Write("Closest grid to center #%d", roundedDiv);
  for(int i = 0; i<roundedDiv; ++i)
  {
    startCell.x -= m_orthoSize;
    startCell.y -= m_orthoSize;
  }

  Log::Write("startCell %f : %f", startCell.x, startCell.y);

  /*
  Grid with even number of cells
  .----.----.----.----.
  |    |    |    |    |
  '----'----'----'----'
  *<--------| ends up here, need to add ortho size/2
  so it ends up in the middle of the cell
  
  Grid with odd number of cells
  .----.----.----.----.----.
  |    |    |    |    |    |
  '----'----'----'----'----.
     *<-------| ends up here (center, what we want)
  */

  if((int)gridAmount % 2 == 0)
  {
    startCell.x += m_orthoSize /2;
    startCell.y += m_orthoSize /2;
    Log::Write("Even number of cells detected");
    Log::Write("startCell %f : %f", startCell.x, startCell.y);
  }

  fb::DxRenderer* pDxRenderer = fb::DxRenderer::Singleton();

  for(m_currentRow = 0; m_currentRow<gridAmount; ++m_currentRow)
  {
    for(m_currentColumn=0; m_currentColumn<gridAmount; ++m_currentColumn)
    {
      m_pCameraManager->GetCamera()->finalMatrix.m[3][0] = startCell.x + m_currentColumn*m_orthoSize;
      m_pCameraManager->GetCamera()->finalMatrix.m[3][2] = startCell.y + m_currentRow*m_orthoSize;
      Sleep(1000);
      // Request capture in present and wait
      m_requestCapture = true;
      while(m_requestCapture)
        Sleep(100);
    }
  }

  fb::GameTimeSettings::Singleton()->m_timeScale = 1.0f;
  Log::Write("Done");
  m_startGenerating = false;
}

//
// Captures an image
// Gets called by IDXGISwapChain::Present
//
void Main::Capture()
{
  if (!m_requestCapture) return;

  ID3D11Texture2D* pBackBuffer = nullptr;
  HRESULT hr = fb::DxRenderer::Singleton()->pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
  if (hr != S_OK)
  {
    Log::Error("Could not get backbuffer for screen capture. Result 0x%X, GetLastError 0x%X", hr, GetLastError());
    m_requestCapture = false;
    return;
  }
  ScratchImage result;
  hr = DirectX::CaptureTexture(fb::DxRenderer::Singleton()->pDevice, fb::DxRenderer::Singleton()->pContext,
    pBackBuffer, result);

  if (hr != S_OK)
  {
    Log::Error("Could not capture backbuffer. Result 0x%X, GetLastError 0x%X", hr, GetLastError());
    m_requestCapture = false;
    return;
  }

  auto mdata = result.GetMetadata();
  ScratchImage cropped;
  cropped.Initialize2D(mdata.format, mdata.height, mdata.height, mdata.arraySize,
    mdata.mipLevels, mdata.miscFlags);

  Rect r = Rect(mdata.width / 2 - mdata.height / 2, 0, mdata.height, mdata.height);
  hr = CopyRectangle(*result.GetImage(0, 0, 0), r, *cropped.GetImage(0, 0, 0), TEX_FILTER_DEFAULT, 0, 0);
  if(hr != S_OK)
  {
    Log::Error("Could not crop captured image. Result 0x%X, GetLastError 0x%X", hr, GetLastError());
    m_requestCapture = false;
    return;
  }

  std::wstring path = L"grid_" + std::to_wstring(m_currentRow) + L"_" + std::to_wstring(m_currentColumn) + L".tga";
  wprintf(L"%s\n", path.c_str());
  hr = SaveToTGAFile(*cropped.GetImage(0, 0, 0), path.c_str());
  //hr = SaveToWICFile(*cropped.GetImage(0,0,0), WIC_FLAGS_IGNORE_SRGB, GUID_ContainerFormatPng, path.c_str(), &GUID_WICPixelFormat128bppRGBFloat);
  if (hr != S_OK)
    Log::Error("Could not save to file. Result 0x%X, GetLastError 0x%X", hr, GetLastError());

  m_requestCapture = false;
}

Main::Main()
{ }

Main::~Main()
{
  Hooks::RemoveHooks();

	m_dllHandle = 0;
  delete m_pCameraManager;
  delete m_pUserInterface;
}
