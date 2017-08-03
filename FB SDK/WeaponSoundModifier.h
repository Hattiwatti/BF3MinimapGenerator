#ifndef _WeaponSoundModifier_H
#define _WeaponSoundModifier_H
#include "Frostbite_Classes.h"
#include "WeaponModifierBase.h"
namespace fb
{
		class WeaponSoundModifier
		: public WeaponModifierBase	// 0x00
	{
	public:
		DataContainer* m_sound;		// 0x08
	}; // 0x0C
};

#endif