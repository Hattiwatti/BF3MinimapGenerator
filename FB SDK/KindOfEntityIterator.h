#ifndef _KindOfEntityIterator_H
#define _KindOfEntityIterator_H
#include "Frostbite_Classes.h"
#include "EntityWorld.h"
namespace fb
{
	template<typename T> struct KindOfEntityIterator 
	:public fb::EntityWorld::EntityIterator
	{
			KindOfEntityIterator()
			{}

			KindOfEntityIterator(fb::EntityWorld* manager,fb::ClassInfo* classId, bool onlyIncludeIterable = true)
			{
				manager->kindOfQuery(classId,this,onlyIncludeIterable);
			}
	};

};

#endif