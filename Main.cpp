#include "Main.h"
#include "Hooks.h"
#include "Util/Log.h"
#include "FB SDK/Frostbite.h"

//const float ORTHO_SIZE = 500.f;

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

  m_pUserInterface = new UserInterface();

  Hooks::Init();

  m_orthoSize = 500.0f;
	m_exit = false;
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
// Function which the drawing thread can call
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

  Log::Write("corner1 %f : %f", corner1.x, corner1.y);
  Log::Write("corner2 %f : %f", corner2.x, corner2.y);
  XMFLOAT2 square(corner2.x - corner1.x, corner2.y - corner1.y);
  Log::Write("square %f : %f", square.x, square.y);
  float sizeAbs = fabs(square.x);

  Log::Write("Absolute size %fx%f", sizeAbs, sizeAbs);

  float gridAmount = sizeAbs / m_orthoSize;
  Log::Write("GridAmount %f", gridAmount);
  if (round(gridAmount) < gridAmount)
    gridAmount += round(gridAmount) + 1;
  else
    gridAmount = round(gridAmount);

  Log::Write("Rounded %f", gridAmount);

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
    *<--------| ends up here (center, what we want)
  */

  if((int)gridAmount % 2 == 0)
  {
    startCell.x += m_orthoSize /2;
    startCell.y += m_orthoSize /2;
    Log::Write("Even number of cells detected");
    Log::Write("startCell %f : %f", startCell.x, startCell.y);
  }

  XMFLOAT2 cameraCell = startCell;

  m_pCameraManager->GetCamera()->finalMatrix.m[3][0] = cameraCell.x;
  m_pCameraManager->GetCamera()->finalMatrix.m[3][2] = cameraCell.y;
  Sleep(1000);

  for(int i = 0; i<gridAmount; ++i)
  {
    for(int j=0; j<gridAmount; ++j)
    {
      Log::Write("%dx%d ", i+1, j+1);
      cameraCell.x += m_orthoSize;
      m_pCameraManager->GetCamera()->finalMatrix.m[3][0] = cameraCell.x;
      Sleep(500);
    }
    cameraCell.x = startCell.x;
    cameraCell.y += m_orthoSize;
    m_pCameraManager->GetCamera()->finalMatrix.m[3][0] = cameraCell.x;
    m_pCameraManager->GetCamera()->finalMatrix.m[3][2] = cameraCell.y;
  }
  printf("\n");
  Log::Write("Done");
  m_startGenerating = false;
}

Main::Main()
{ }

Main::~Main()
{
  Hooks::RemoveHooks();

	m_dllHandle = 0;
  delete m_pCameraManager;
}
