#ifndef _ClientStanceFilterComponent_H
#define _ClientStanceFilterComponent_H
#include "FB SDK/Frostbite_Classes.h"
namespace fb
{
	class ClientStanceFilterComponent
	{
	public:
		PAD(0x4);																	//0x00
		StanceFilterComponentData *StanceFilterData;
		PAD(0x30);
		const class ClientEntryComponent * m_controllingEntry;                     // this+0x38

	}; // fb::ClientStanceFilterComponent

};

#endif