#ifndef _WeaponModifier_H
#define _WeaponModifier_H
#include "Frostbite_Classes.h"
#include "WeaponMiscModifierSettings.h"
#include "WeaponShotModifier.h"
#include "WeaponProjectileModifier.h"
#include "WeaponAimingSimulationModifier.h"
#include "WeaponAimingConfigurationModifier.h"
#include "WeaponAnimTypeModifier.h"
#include "WeaponMagazineModifier.h"
#include "WeaponZoomModifier.h"
namespace fb
{
	class WeaponModifier
	{
	public:
		PAD(0xA8);																	// 0x00
		WeaponMiscModifierSettings m_weaponMiscModifier;							// 0xA8
		PAD(0x4);																	// 0xAC
		WeaponFiringDataModifier* m_weaponFiringDataModifier;						// 0xB0
		WeaponFiringEffectsModifier* m_weaponFiringEffectsModifier;					// 0xB4
		WeaponSoundModifier* m_weaponSoundModifier;									// 0xB8
		WeaponShotModifier* m_weaponShotModifier;									// 0xBC
		WeaponProjectileModifier* m_weaponProjectileModifier;						// 0xC0
		WeaponAimingSimulationModifier* m_weaponAimingSimulationModifier;			// 0xC4
		WeaponAimingConfigurationModifier* m_weaponAimingConfigurationModifier;		// 0xC8
		WeaponAnimTypeModifier* m_weaponAnimTypeModifier;							// 0xCC
		WeaponMagazineModifier* m_weaponMagazineModifier;							// 0xD0
		WeaponZoomModifier* m_weaponZoomModifier;									// 0xD4
	}; // 0xD8


};

#endif