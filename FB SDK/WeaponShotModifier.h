#ifndef _WeaponShotModifier_H
#define _WeaponShotModifier_H
#include "Frostbite_Classes.h"
#include "WeaponModifierBase.h"
namespace fb
{
	class WeaponShotModifier
		: public WeaponModifierBase			// 0x00
	{
	public:
		PAD(0x8);							// 0x08
		Vec3 m_initialSpeed;				// 0x10
		INT m_numberOfBulletsPerShell;		// 0x20
	}; // 0x24
};

#endif