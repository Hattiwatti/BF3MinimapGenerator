#ifndef __BF3Classes__H_
#define __BF3Classes__H_

#pragma warning (disable:4099) //  type name first seen using 'class' now seen using 'struct'
#pragma warning (disable:4244) // '+=' : conversion from 'int' to 'WORD', possible loss of data
#pragma warning (disable:4305) // truncation from 'double' to 'float
#pragma warning (disable:4800) //forcing value to bool 'true' or 'false'

#include <d3d11.h>
#include <DirectXMath.h>

#define CONCAT_IMPL(x, y) x##y
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)
#define PAD(SIZE) BYTE MACRO_CONCAT(_pad, __COUNTER__)[SIZE];
#define POINTERCHK( pointer ) ( pointer  && pointer !=0  && HIWORD( pointer ) )

using namespace DirectX;

#include "Offsets.h"
#include "EASTL_Includes.h"
#include "Enumerations.h"
#include "EA.h"
#include "Juice.h"
#include "Frostbite_Classes.h"
#include "ClassT.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Mat4.h"
#include "LinearTransform.h"
#include "Quat.h"
#include "QuatTransform.h"
#include "AxisAlignedBox.h"
#include "Plane.h"
#include "Frustum.h"
#include "Color32.h"
#include "Havok.h"
#include "ScreenshotModule.h"
#include "ISocket.h"
#include "BitArray.h"
#include "MessageListener.h"
#include "eastl_arena_allocator.h"
#include "InBitStream.h"
#include "OutBitStream.h"
#include "Timer.h"
#include "network.h"
#include "online.h"
#include "ant.h"
#include "PlayerManager.h"
#include "ControlObjectState.h"
#include "MemoryArena.h"
#include "String.h"
#include "ITypedObject.h"
#include "DataContainer.h"
#include "Asset.h"
#include "Score.h"
#include "DebugRender.h"
#include "Pad.h"
#include "MotionController.h"
#include "Device.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "BorderInputNode.h"
#include "System.h"
#include "PropertyModificationListener.h"
#include "SupportsWeakPtr.h"
#include "PlayerData.h"
#include "GameTime.h"
#include "WorldRenderer.h"
#include "Level.h"
#include "DataBusData.h"
#include "EntityBusData.h"
#include "EventConnection.h"
#include "Blueprint.h"
#include "DebrisManager.h"
#include "PhysicsEntityUserData.h"
#include "IPhantom.h"
#include "IMoving.h"
#include "IRotation.h"
#include "IPhysics.h"
#include "IHavok.h"
#include "PhysicsRenderParams.h"
#include "Hook.h"
#include "MaterialGridManager.h"
#include "EntityEvent.h"
#include "DataContext.h"
#include "EntityBus.h"


#include "MaterialGridData.h"
#include "MaterialContainerPair.h"
#include "MaterialRelationPropertyPair.h"
#include "MaterialInteractionGridRow.h"
#include "PhysicsEntityBaseRayCast.h"
#include "PhysicsEntityContainer.h"
#include "EntityGridQueryJobData.h"


#include "IPhysicsRayCaster.h"
#include "HavokPhysicsManager.h"
#include "WeakTokenHolder.h"
#include "OnlineID.h"
#include "Player.h"
#include "EntryInput.h"
#include "EntityCollection.h"
#include "SpottingComponentData.h"
#include "GameObjectData.h"
#include "TeamInfo.h"
#include "GameEntityData.h"
#include "TeamEntityData.h"
#include "GameRenderer.h"
#include "WeaponComponent.h"
#include "EntryComponent.h"
#include "CameraComponent.h"
#include "CacheData.h"
#include "PropertyWriter.h"

#include "Main.h"

#include "CharacterPhysicsEntity.h"
#include "RayCastHit.h"
#include "RayCastResult.h"
#include "SoldierEntity.h"
#include "BulletEntityData.h"

#include "CtrRefBase.h"
#include "ComponentInfo.h"
#include "ComponentCollection.h"
#include "FieldInfo.h"
#include "TypeInfo.h"
#include "TypeManager.h"
#include "ClassInfo.h"
#include "ModuleManager.h"
#include "KindOfEntityIterator.h"






#include "Mesh.h"
#include "Ragdoll.h"
#include "CameraShakeManager.h"

#include "Client.h"
#include "ClientGameContext.h"
#include "ClientComponent.h"
#include "ClientSpottingComponent.h"
#include "ClientSpottingTargetComponent.h"
#include "ClientCameraComponent.h"
#include "ClientPlayerView.h"
#include "ClientCameraContext.h"
#include "ClientGameEntity.h"
#include "ClientPlayer.h"
#include "ClientPhysicsEntity.h"
#include "ClientControllableEntity.h"
#include "ClientCharacterEntity.h"
#include "ClientAntAnimatableComponent.h"
#include "ClientProximityHookImpl.h"
#include "ClientEntryComponentSound.h"
#include "ClientGameWorld.h"
#include "ClientSoldierWeapon.h"
#include "ClientBoneCollisionComponent.h"
#include "ClientSoldierAimingSimulation.h"
#include "ClientEntryComponent.h"
#include "ClientAnimatedSoldierWeaponHandler.h"
#include "ClientSoldierWeaponsComponent.h"
#include "ClientWeapon.h"	
#include "ClientSoldierEntity.h"
#include "ClientVehicleEntity.h"


#include "Entity.h"
#include "EntityStuff.h"

#include "PhysicsEntity.h"
#include "PhysicsEntityData.h"

#include "Vehicle.h"
	
#include "AnimatedSoldierWeapon.h"
#include "WeaponFiringShooter.h"
#include "WeaponSwayCallbackImpl.h"
#include "WeaponModifier.h"	
#include "WeaponProjectileModifier.h"	
#include "WeaponShotModifier.h"
#include "WeaponEntityData.h"
#include "WeaponInfo.h"
#include "WeaponOffsetData.h"
#include "WeaponSwitching.h"



#include "Rumble.h"
#include "Level.h" //
#include "UI.h"    //
#include "GameTime.h"
#include "WorldRenderer.h"	//

#include "IRender.h"	//
#include "IStateRenderer.h"	//
#include "ScreenRenderer.h"	//

#include "Snowroller.h"
#include "Server.h"	//

#endif // __BF3Classes__H_
