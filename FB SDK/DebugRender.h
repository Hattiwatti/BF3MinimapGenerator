#ifndef _DEBUGRENDER_H
#define _DEBUGRENDER_H

//#include "../Frostbite_classes.h"

namespace fb
{

	enum DebugGeometryType
	{

		DebugGeometryType_Triangle3d,                    // constant 0x0
		DebugGeometryType_Line3d,                    // constant 0x1
		DebugGeometryType_Triangle2d,                     // constant 0x2
		DebugGeometryType_Line2d,                     // constant 0x3
		DebugGeometryType_Font2d,                     // constant 0x4
		DebugGeometryTypeCount                   // constant 0x5

	}; // fb::DebugGeometryType

	enum DebugRenderCmdId
	{

		DebugRenderCmdId_Text2d,                     // constant 0x0
		DebugRenderCmdId_Text3d,                     // constant 0x1
		DebugRenderCmdId_TextLog,                     // constant 0x2
		DebugRenderCmdId_Vertices,                     // constant 0x3
		DebugRenderCmdId_Sphere,                     // constant 0x4
		DebugRenderCmdIdCount                     // constant 0x5

	}; // fb::DebugRenderCmdId

	enum DebugRenderFrameType
	{

		 DebugRenderFrameType_Immediate,                  // constant 0x0
		 DebugRenderFrameType_OneFrameLatency,                     // constant 0x1
		 DebugRenderFrameType_Discard                     // constant 0x2

	}; // fb::DebugRenderFrameType

	class DebugRenderStateCombo
	{

		unsigned char transparent;                     // 0x0, len(0x1)
		unsigned char doubleSided;                     // 0x1, len(0x1)
		unsigned char depthTest;                     // 0x2, len(0x1)
		unsigned char depthWrite;                     // 0x3, len(0x1)
		unsigned char shadingMode;                     // 0x4, len(0x2)

	}; // fb::DebugRenderStateCombo

	class DebugRenderCmd
	{

		DebugRenderCmdId id;                     // 0x0
		DebugRenderStateCombo state;                     // 0x4
		unsigned sortOrder;                     // 0x8
		unsigned int size;                     // 0xC

	}; // fb::DebugRenderCmd


	class DebugRenderVertex
	{

		/*struct fb::Tuple3<float> */ void* pos;                     // 0x0
		struct fb::Color32 color;                     // 0xC
		/*struct fb::Tuple3<float>*/ void * normal;                     // 0x10
		unsigned int pad;                     // 0x1C

	}; // fb::DebugRenderVertex

	class DebugRenderStats2
	{

		unsigned int/*[0x5] */typeVertexCounts;                     // 0x0
		unsigned int/*[0x5]*/ typeDrawCallCounts;                     // 0x14
		unsigned int/*[0x5]*/ commandCounts;                     // 0x28
		unsigned int/*[0x5]*/ commandSizes;                     // 0x3C

	}; // fb::DebugRenderStats2

	class DebugRenderCmd_Vertices
		:public DebugRenderCmd   // Inherited class at offset 0x0
	{
/*
		class fb::DebugRenderCmd // Inherited class at offset 0x0
		{

			enum fb::DebugRenderCmdId id;                     // 0x0
			struct fb::DebugRenderStateCombo state;                     // 0x4
			unsigned int sortOrder;                     // 0x8
			unsigned int size;                     // 0xC

		}; // fb::DebugRenderCmd
		*/
		DebugGeometryType type;                     // 0x10
		unsigned int vertexCount;                     // 0x14
		DebugRenderVertex/*[0x0] */vertices;                     // 0x18
		
	}; // fb::DebugRenderCmd_Vertices

	class IDebugRenderBackend
	{

		virtual void beginCmdList(unsigned int, unsigned int *, struct fb::DebugRenderCmd * *);	// V: 0x0
		virtual void endCmdList(unsigned int, unsigned int);	// V: 0x4
		virtual void queueFrame(enum fb::DebugRenderFrameType, const char *, unsigned int, const unsigned int *);	// V: 0x8
		virtual void queueExternalFrame(const char *, unsigned int, struct fb::DebugRenderCmd *);	// V: 0xC
		virtual void draw(float, const class fb::RenderView &, struct fb::DebugRenderStats2 *);	// V: 0x10
		virtual struct fb::Tuple2<unsigned int> getScreenResolution();	// V: 0x14
		
	}; // fb::IDebugRenderBackend


	class DebugRenderer
	{
	public:
		static DebugRenderer* Singleton()
		{
			typedef fb::DebugRenderer* (__stdcall* tGetDebugRenderer)(void);
			tGetDebugRenderer GetDebugRenderer=(tGetDebugRenderer)0x446130;//CSigManager::Singleton()->dwOFFSET_DEBUGRENDERER;//0x004B27E0;
			return GetDebugRenderer();
		}
		void DrawBox(fb::AxisAlignedBox  &aab, fb::LinearTransform &transform,DWORD dwColor)
		{
			typedef void* (__thiscall* tDrawBox)(fb::DebugRenderer*,fb::AxisAlignedBox&,fb::LinearTransform&,DWORD);
			tDrawBox _DrawBox=(tDrawBox)0x0043A260;
			_DrawBox(this,aab,transform,dwColor);
		}
		void DrawLineBox(fb::AxisAlignedBox  &aab, fb::LinearTransform &transform,DWORD dwColor)
		{
			static __declspec(align(16)) fb::AxisAlignedBox box;
			static __declspec(align(16)) fb::LinearTransform trans;
			box.max=aab.max;
			box.min=aab.min;
			trans.forward=transform.forward;
			trans.left=transform.left;
			trans.up=transform.up;
			trans.trans=transform.trans;
			typedef void* (__thiscall* tDrawBox)(fb::DebugRenderer*,fb::AxisAlignedBox&,fb::LinearTransform&,DWORD);
			tDrawBox _DrawBox=(tDrawBox)0x0043E0E0;
			_DrawBox(this,box,trans,dwColor);
		}
		void DrawSphere(fb::Vec3 &pos, float radius, DWORD color, bool renderLines, bool scalesmall)
		{
			typedef void (__thiscall *tDrawSphere)(fb::DebugRenderer*,fb::Vec3&, float, DWORD,bool renderLines, bool scalesmall);
			tDrawSphere EngDrawSphere=(tDrawSphere)0x0043AF20;
			EngDrawSphere(this,pos,radius,color,renderLines,scalesmall);
		};
	};

	class DebugRenderer2
	{
	public:

		/*	struct DebugRenderStateCombo[0x8] m_stateStack;                     // 0x4
		struct DebugRenderStateCombo * m_state;                     // 0xC
		struct IDebugRenderBackend * m_backend;                     // 0x10
		struct DebugRenderCmd_Vertices [0x5]* m_verticesCmds;                     // 0x14
		unsigned int m_vertexCacheMaxCount;                     // 0x28
		unsigned int m_vertexCacheUsedCount;                     // 0x2C
		DebugGeometryType m_vertexCacheType;                     // 0x30
		struct DebugRenderVertex * m_vertexCache;                     // 0x34
		unsigned int m_cmdListId;                     // 0x38
		unsigned int m_cmdListSize;                     // 0x3C
		unsigned int m_cmdListUsed;                     // 0x40
		struct DebugRenderCmd * m_cmdList;                     // 0x44
		void* m_frameCmdListIds; //	class eastl::vector<unsigned int,fb::eastl_arena_allocator>                    // 0x48
		*/

		static DebugRenderer2* Singleton()
		{
			typedef fb::DebugRenderer2* (__stdcall* tGetDebugRenderer2)(void);
			tGetDebugRenderer2 GetDebugRenderer2=(tGetDebugRenderer2)(fb::DebugRenderer2*)DBGRENDERER2;
			return GetDebugRenderer2();
		}

		//from jugga 
		/*
		static DebugRenderer2* Singleton(void) //Credits to KingOrgy for giving me some hints
		{
			typedef fb::DebugRenderer2* (__stdcall* fb__DebugRenderManager_getThreadContext_t)(void);
			fb__DebugRenderManager_getThreadContext_t fb__DebugRenderManager_getThreadContext=(fb__DebugRenderManager_getThreadContext_t)OFFSET_DBGRENDERER2;
			return fb__DebugRenderManager_getThreadContext();
		}
		
		*/
		void drawText(int x, int y, Color32 color, char* text, float scale)
		{
				typedef void (__thiscall *tdrawText)(fb::DebugRenderer2*,int, int, char*, Color32,float);
				tdrawText mdrawText=(tdrawText)0x004B7070;  
				mdrawText(this,x,y,text,color,scale);
		}
		
		void drawLine2d(Tuple2<float>* pos1, Tuple2<float>* pos2, Color32 color)
		{
			typedef void (__thiscall *tdrawLine2d)(fb::DebugRenderer2*,Tuple2<float>*, Tuple2<float>*, Color32);
			tdrawLine2d mdrawLine2d=(tdrawLine2d)0x4B92D0;
			mdrawLine2d(this,pos1,pos2,color);
		}

		void drawLineRect2d(Tuple2<float>* minpos, Tuple2<float>* maxpos, Color32 color)
		{
			typedef void (__thiscall *tdrawLineRect2d)(fb::DebugRenderer2*,Tuple2<float>*, Tuple2<float>*, Color32);
			tdrawLineRect2d mdrawLineRect2d=(tdrawLineRect2d)0x4B9BA0;
			mdrawLineRect2d(this,minpos,maxpos,color);
		}

		void drawRect2d(Tuple2<float>* minpos, Tuple2<float>* maxpos, Color32 color)
		{
			typedef void (__thiscall *tdrawRect2d)(fb::DebugRenderer2*,Tuple2<float>*, Tuple2<float>*, Color32);
			tdrawRect2d mdrawRect2d=(tdrawRect2d)0x4B9DB0;
			mdrawRect2d(this,minpos,maxpos,color);
		}

		void	DrawSphere(fb::Vec3 pos,float radius, DWORD col)
		{
			fb::DebugRenderer2* pDR=fb::DebugRenderer2::Singleton();
			if(!pDR)
			{
				return;
			}
			__declspec(align(16)) fb::Vec3 _pos;
			_pos.x=pos.x;
			_pos.y=pos.y;
			_pos.z=pos.z;
			_pos.w=pos.w;
			typedef void(__thiscall* tDrawSphere)(fb::DebugRenderer2*,fb::Vec3*, float, DWORD, bool, bool);
			tDrawSphere DrawSphere=(tDrawSphere)DBGRENDRAWSPHERE;
			DrawSphere(pDR,&_pos,radius,col,false,false);
		}

		void DrawTriangle2d(float x0, float y0,float x1, float y1,float x2, float y2,DWORD col)
		{
			fb::DebugRenderer2* pDR=fb::DebugRenderer2::Singleton();
			if(!pDR)
			{
				return;
			}
			typedef void (__thiscall* tDrawSingleColorTriangle)(fb::DebugRenderer2*, eastl::Tuple<float>*, eastl::Tuple<float>*, eastl::Tuple<float>*,DWORD);
			tDrawSingleColorTriangle m_DrawSingleColorTriangle=(tDrawSingleColorTriangle)DBGRENDRAWTRIANGLE;
			eastl::Tuple<float> t1, t2, t3;
			t1._1=x0;
			t1._2=y0;
			t2._1=x1;
			t2._2=y1;
			t3._1=x2;
			t3._2=y2;
			m_DrawSingleColorTriangle(pDR,&t1,&t2,&t3,col);
		}

	};


};

#endif