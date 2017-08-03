#ifndef _AttributeSpec_H
#define _AttributeSpec_H
#include "Frostbite_Classes.h"
namespace fb
{

	class AttributeSpec
	{
		const char * attributeName;                     // 0x0
		AttributeArgument * attributeArguments;                     // 0x4
	}; // fb::AttributeSpec

};

#endif