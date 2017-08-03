#ifndef _WeaponSpeedData_H
#define _WeaponSpeedData_H
#include "Frostbite_Classes.h"
#include "DataContainer.h"
namespace fb
{
	class WeaponSpeedData
		: public DataContainer		// 0x00
	{
	public:
		FLOAT m_zoomOutSpeed;		// 0x08
		FLOAT m_zoomInSpeed;		// 0x0C
		FLOAT m_unDeploySpeed;		// 0x10
		FLOAT m_deploySpeed;		// 0x14
	}; // 0x18

};

#endif