#ifndef _WeaponInfo_H
#define _WeaponInfo_H
#include "Frostbite_Classes.h"
#include "EntryComponent.h"
#include "ClientWeaponComponentPrediction.h"
#include "ClientWeaponComponentReplication.h"
namespace fb
{
		class WeaponInfo
		:public EntryComponent::WeaponInfo
    {
	public:
        ClientWeaponComponent &  m_weapon;                     // this+0x4
        ClientWeaponComponentReplication & m_replicated;                     // this+0x8
        ClientWeaponComponentPrediction & m_predicted;                     // this+0xC
        ClientStanceFilterComponent * m_stanceFilterComponent;                     // this+0x10

    }; // WeaponInfo 

};

#endif