#ifndef _ClientAntAnimatableComponent_H
#define _ClientAntAnimatableComponent_H
#include "Frostbite_Classes.h"
namespace fb
{
	class AntAnimatableComponent // Inherited class at offset 0x10
	{

		virtual void setAnimationWorldTransform(const struct fb::LinearTransform &, float, enum fb::AnimationTransformMode, enum fb::GameplayBones, void *, int);	// V: 0x0
		/*class GameAnimatable*/void* m_handler;                     // 0x10
		eastl::fixed_vector<LinearTransform,4,1,eastl_arena_allocator> m_boneTransforms;                     // 0x300
		bool m_isActive;                     // 0x324
	
	}; // fb::AntAnimatableComponent


	class ClientAntAnimatableComponent
	{
	public:
		BYTE pad_001[0x20];
		BYTE pad_002[0xD0];
		bool m_hadVisualUpdate;
	};

};

#endif