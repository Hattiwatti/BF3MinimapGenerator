#ifndef _WeaponFiringDataModifier_H
#define _WeaponFiringDataModifier_H
#include "Frostbite_Classes.h"
#include "WeaponModifierBase.h"
namespace fb
{
		class WeaponFiringDataModifier
		: public WeaponModifierBase			// 0x00
	{
	public:
		DataContainer* m_weaponFiring;		// 0x08
	}; // 0x0C
};

#endif