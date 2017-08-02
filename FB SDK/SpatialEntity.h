#ifndef _SpatialEntity_H
#define _SpatialEntity_H
#include "Frostbite_Classes.h"
#include "Entity.h"
namespace fb
{
	class SpatialEntity
		: public Entity				// 0x00
	{
	public:
		//virtual void func0();//getType(); //0 // V: 0x0
		virtual void propertyChanged(/*fb::PropertyModificationListener::PropertyModification const &*/);//1 // V: 0x4
        virtual void listenToParentChanges(void);//2 // V: 0x8
        virtual bool isPropertyChangedAllowed(void);//3 // V: 0xC
        virtual void _event(/*fb::EntityEvent const *)*/);//4 // V: 0x10
        virtual void editEvent(/*fb::DataUpdateEvent const **/);//5 // V: 0x14
        virtual void getDebugName(/*fb::StringBuilderBase &,bool*/);//6 // V: 0x18
        virtual void getPeerBus(void);//7  // V: 0x1C
        virtual void getPeerData(void);//8  V: 0x20
        virtual void Function9();//9  0x24
        virtual void computeWorldTransform(LinearTransform &);//10 0x28
        virtual void getPeerSubBus(void);//11 0x2C
        virtual void getRecordingData(/*fb::EntityRecordingData **/);//12  0x30
        virtual void onCreate(/*fb::EntityBusPeerCreationInfo &*/);//13 0x34
        virtual void onDestroy(void);//14 0x38
        virtual void Function15(); // 0x3C
        virtual void onSaveCreate(/*fb::SaveOutStream &*/); // 0x40
        virtual void onInit(/*fb::EntityInitInfo &*/); // 0x44
        virtual void onSaveInit(/*fb::SaveOutStream &*/);  // 0x48
        virtual void onDeinit(/*fb::EntityDeinitInfo &*/); // 0x4C
        virtual void onDeinitNotAllowed(/*fb::EntityDeinitInfo &*/); // 0x50
        virtual void onInitOwnedEntity(/*fb::EntityInitInfo &,fb::Entity **/);  // 0x54
        virtual void getTransform(LinearTransform &);//22 - 0x58 
        virtual void setTransform(LinearTransform const &);//23 - 5C 
        virtual void computeBoundingBoxWorldTransform(fb::LinearTransform &); // V: 0x60
        virtual void computeBoundingBox(fb::AxisAlignedBox &); // V: 0x64 25
        virtual void visualCullScreenArea(void); // V: 0x68
        virtual void onHiddenToggled(bool); // V: 0x6C
        virtual void spawn(fb::LinearTransform const *,void *,bool);//28 - 0x70 
        virtual void needPrePhysicsUpdate(void); // V: 0x74
        virtual void prePhysicsUpdate(/*fb::EntityUpdateInfo const &*/); // V: 0x78
        virtual void prePhysicsQuery(/*fb::EntityUpdateInfo const &*/); // V: 0x7c
        virtual void needPostPhysicsUpdate(void); // V: 0x80
        virtual void postPhysicsUpdate(EntityUpdateInfo const &); // V: 0x84
        virtual void postPhysicsQuery(/*fb::EntityUpdateInfo const &*/); // V: 0x88
        virtual void needPostFrameUpdate(void); // V: 0x8c
        virtual void postFrameUpdate(/*fb::EntityUpdateInfo const &*/); // V: 0x90
        virtual void postFrameQuery(/*fb::EntityUpdateInfo const &*/); // V: 0x94
        virtual void needFrameInterpolationUpdate(void); // V: 0x98
        virtual void frameInterpolationUpdate(/*fb::EntityUpdateInfo const &*/); // V: 0x9c
        virtual void frameInterpolationQuery(/*fb::EntityUpdateInfo const &*/); // V: 0x100
        virtual void onSpawn(/*fb::GameEntity::SpawnInfo const &*/); 
        virtual void onUnSpawn(/*fb::GameEntity::UnSpawnInfo const &*/); 
        virtual void onDeinit1(/*fb::GameEntity::GameEntityDeinitInfo &*/); 
        virtual void worldTransformChanged(fb::LinearTransform const &,bool); 
        virtual void onComponentWorldTransformDirty(void); 
        virtual void onComponentUpdateRequiredChanged(void); 
        virtual void onComponentLocalBoundingBoxDirty(void); 
        virtual void createUpdater(/*fb::UpdatePass*/); 
        virtual void getUpdaters(void); 
        virtual void meshModel(void); 
        virtual void visualUpdate( float deltaTime );//fn 51 - 0xCC 

		DWORD m_cullGridId;                    // 0x0C
		
		__forceinline Vec3* GetEntityOrigin()
		{
			LinearTransform tmp;
			this->getTransform( tmp );
			return &tmp.trans;
		}

		__forceinline bool GetWorldOrigin(Vec3* v)
		{
			LinearTransform tmp;
			this->computeWorldTransform( tmp );
			memcpy_s(v, sizeof(fb::Vec3), &tmp.trans, sizeof(fb::Vec3));
			if(v) return true;
			return false;
		}
		//DWORD m_cullGridId;			// 0x0C
	}; // 0x10


};

#endif