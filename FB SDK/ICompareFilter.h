#ifndef _ICompareFilter_H
#define _ICompareFilter_H
#include "Frostbite_Classes.h"
#include "TypeInfo.h"
#include "FieldInfo.h"
namespace fb
{
	
	class ICompareFilter
	{

		virtual bool filterField(TypeInfo *, FieldInfo::FieldInfoData *);	// V: 0x0
			
	}; // fb::ICompareFilter

};

#endif