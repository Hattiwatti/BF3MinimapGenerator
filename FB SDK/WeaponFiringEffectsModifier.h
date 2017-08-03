#ifndef _WeaponFiringEffectsModifier_H
#define _WeaponFiringEffectsModifier_H
#include "Frostbite_Classes.h"
#include "WeaponModifierBase.h"
namespace fb
{
	class WeaponFiringEffectsModifier
		: public WeaponModifierBase				// 0x00
	{
	public:
		Array<FireEffectData> m_fireEffects1p;	// 0x08
		Array<FireEffectData> m_fireEffects3p;	// 0x0C
	}; // 0x10
};

#endif