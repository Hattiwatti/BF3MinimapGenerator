#ifndef _GameRenderer_H
#define _GameRenderer_H

#include "RenderView.h"

namespace fb
{
	class GameRenderViewParams
	{
	public:
		RenderView view;						// 0x00
		RenderView prevView;					// 0x480
		RenderView secondaryStreamingView;		// 0x900
		INT secondaryStreamingViewEnable;		// 0xD80
		PAD(0xC);								// 0xD84
		LinearTransform firstPersonTransform;		// 0xD90
	};

	class IGameRenderer
	{
	public:
		virtual VOID Function0();												// V: 0x0
		virtual VOID Function1();												// V: 0x4
		virtual VOID init();													// V: 0x8
		virtual VOID postLoadInit();											// V: 0xC
		virtual VOID createUpdateJob(FLOAT, FLOAT, LPVOID, LPVOID, LPVOID);		// V: 0x10
		// valid Draw Job
		virtual VOID joinUpdateJob();											// V: 0x14
		virtual VOID setJobEnable(BOOL);										// V: 0x18
		virtual BOOL getJobEnable();											// V: 0x1C
		virtual VOID onUnloadLevel();											// V: 0x20
		virtual INT getAffinity();												// V: 0x24
		virtual XMFLOAT2A getResolution();									// V: 0x28
		virtual VOID addModule(INT, LPVOID);									// V: 0x2C
		virtual VOID removeModule(INT);											// V: 0x30
		//  valid Draw Job
		virtual class GameRenderSettings* getSettings();					// V: 0x34
		//this
		virtual class ScreenRenderer* getScreenRenderer();						// V: 0x38
		virtual VOID updatePerfOverlay(BOOL, FLOAT);							// V: 0x3C
		// valid Draw Job
		virtual VOID resetPerfOverlay();										// V: 0x40
		virtual BOOL isFadeInAllowed();											// V: 0x44
		virtual VOID setVsyncEnable(BOOL);										// V: 0x48
		// valid Draw Job
		virtual BOOL getVsyncEnable();											// V: 0x4C
		virtual VOID setPresentEnable(BOOL);									// V: 0x50
		virtual VOID getAdapterInformation(LPVOID, UINT&, UINT&);				// V: 0x54
		virtual const RenderView& getTempDeprecatedView();						// V: 0x58

		INT m_refCount;															// 0x04
	}; // 0x08

	class GameRenderer :
		public IGameRenderer
	{
	public:
		PAD(0x48);							// 0x08
		GameRenderViewParams m_viewParams;	// 0x50

	public:
		BOOL worldToScreen( Vec3 *world, Vec3 *screen )
		{
			if( !world || !screen )
				return FALSE;

			if( this->m_viewParams.view.Update( ) == FALSE )
				return FALSE;

			DWORD dwRet;
			LinearTransform *view = &this->m_viewParams.view.m_viewMatrix;
			LinearTransform *projection = &this->m_viewParams.view.m_projectionMatrix;
			DWORD fb__projectToScreenSpace = 0x00EF1590;
			__asm
			{
				push projection
				push view
				push world
				push screen
				call fb__projectToScreenSpace
				mov dwRet, eax
				pop eax
				pop eax
				pop eax
				pop eax
			}
			
			return TRUE;//returns screen
		}

    void ScreenToWorld(XMFLOAT2 pos, XMVECTOR& out)
    {
      fb::DxRenderer* pDxRenderer = fb::DxRenderer::Singleton();
      XMMATRIX projectionMatrix = (XMMATRIX&)m_viewParams.view.m_projectionMatrix;

      /*
      if (m_viewParams.view.m_desc.type == 1)
      {
        projectionMatrix = XMMatrixOrthographicRH(pDxRenderer->m_screenInfo.m_nWidth, pDxRenderer->m_screenInfo.m_nHeight,
          m_viewParams.view.m_desc.nearPlane, m_viewParams.view.m_desc.farPlane);
      }
      else
      {
        float aspect = (float)pDxRenderer->m_screenInfo.m_nWidth / (float)pDxRenderer->m_screenInfo.m_nHeight;
          projectionMatrix = XMMatrixPerspectiveFovRH(m_viewParams.view.m_desc.fovY, aspect,
          m_viewParams.view.m_desc.nearPlane, m_viewParams.view.m_desc.farPlane);
      }*/

      out.m128_f32[0] = (((2.0f * pos.x) / pDxRenderer->m_screenInfo.m_nWidth) - 1.0f) / projectionMatrix.r[0].m128_f32[0];
      out.m128_f32[1] = (((-2.0f * pos.y) / pDxRenderer->m_screenInfo.m_nHeight) + 1.0f) / projectionMatrix.r[1].m128_f32[1];
      out.m128_f32[2] = -1;

      /*
      XMMATRIX firstPerson = (XMMATRIX&)m_viewParams.firstPersonTransform;
      XMMATRIX viewMatrix = XMMatrixIdentity();

      viewMatrix.r[0] = XMVectorSet(firstPerson.r[0].m128_f32[0], firstPerson.r[1].m128_f32[0], firstPerson.r[2].m128_f32[0], 0);
      viewMatrix.r[1] = XMVectorSet(firstPerson.r[0].m128_f32[1], firstPerson.r[1].m128_f32[1], firstPerson.r[2].m128_f32[1], 0);
      viewMatrix.r[2] = XMVectorSet(firstPerson.r[0].m128_f32[2], firstPerson.r[1].m128_f32[2], firstPerson.r[2].m128_f32[2], 0);
      
      viewMatrix.r[3] = XMVectorSet(-XMVector3Dot(firstPerson.r[3], firstPerson.r[0]).m128_f32[0],
                                    -XMVector3Dot(firstPerson.r[3], firstPerson.r[1]).m128_f32[0],
                                    -XMVector3Dot(firstPerson.r[3], firstPerson.r[2]).m128_f32[0],
                                    0);

      XMMATRIX inverseViewMatrix = XMMatrixInverse(nullptr, viewMatrix);*/
      
		  out = XMVector3TransformNormal(out, (XMMATRIX&)m_viewParams.view.m_viewMatrixInverse);
      out = XMVector3Normalize(out);
    }

		static GameRenderer* Singleton()
		{
			return *(GameRenderer**)(0x02384D78);
		}
	};

  class GameRenderSettings
  {
  public:
    BYTE Pad000[0x10];
    float m_ForceOrthoViewSize;
    BYTE Pad014[0x90];
    BYTE m_ForceOrthoViewEnable;
    BYTE Pad0A5[0xA];
    BYTE m_ForceSquareOrthoView;
  };

};

#endif