#ifndef _WeaponProjectileModifier_H
#define _WeaponProjectileModifier_H
#include "Frostbite_Classes.h"
#include "WeaponModifierBase.h"
namespace fb
{
	class WeaponProjectileModifier
		: public WeaponModifierBase				// 0x00
	{
	public:
		ProjectileEntityData* m_projectileData;	// 0x08
	}; // 0x0C
};

#endif