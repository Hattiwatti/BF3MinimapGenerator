#ifndef _FieldInfoImpl_H
#define _FieldInfoImpl_H
#include "Frostbite_Classes.h"
#include "FieldInfo.h"
namespace fb
{
	
	class FieldInfoImpl
		:public FieldInfo
	{
		TypeInfo * m_declaringType;                     // 0x8
		USHORT  m_fieldIndex;                     // 0xC
		USHORT  m_attributeMask;                     // 0xE
	}; // fb::FieldInfoImpl

};

#endif