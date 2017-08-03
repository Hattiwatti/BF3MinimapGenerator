#ifndef _WeaponName_H
#define _WeaponName_H
#include "Frostbite_Classes.h"
namespace fb
{
	
	class WeaponName
	{
	public:
		unsigned char pad0[8];
		eastl::basic_string<char> m_name;
	};

};

#endif