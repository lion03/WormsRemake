/**
\file	Weapon.h

\brief	Declares the weapon class.
*/

#pragma once
#include "Projectile.h"
#include "External/spine/Animation.h"
#include "External/spine/AnimationState.h"
#include "External/spine/AnimationStateData.h"
#include "External/spine/Atlas.h"
#include "External/spine/AtlasAttachmentLoader.h"
#include "External/spine/Attachment.h"
#include "External/spine/AttachmentLoader.h"
#include "External/spine/Bone.h"
#include "External/spine/BoneData.h"
#include "External/spine/RegionAttachment.h"
#include "External/spine/Skeleton.h"
#include "External/spine/SkeletonData.h"
#include "External/spine/SkeletonJson.h"
#include "External/spine/Skin.h"
#include "External/spine/Slot.h"
#include "External/spine/SlotData.h"
#include "External/spine/spine-sfml.h"
#include "Macros.h"
#include <string>
#include <memory>
#include "ProjectileCounter.h"
class Worm;

/**
\brief	Weapon.
*/

class Weapon
{
public:

	/**
	\brief	Initializes a new instance of the Weapon class.
	*/

	Weapon(const std::string &attachmentName,uint8 burst = 0);

	/**
	\brief	Finalizes an instance of the Weapon class.
	*/

	virtual ~Weapon(void);

	/**
	 \brief	Fire shot.
	
	 \param	power	The power.
	 */

	virtual void fireShot(float power) = 0;

	virtual void loadShot(){}

	/**
	 \brief	Fires.
	
	 \param	pos							 	The position.
	 \param	dirVec						 	The dir vector.
	 \param	angle						 	The angle.
	 \param	power						 	The power.
	 \param [in,out]	world			 	If non-null, the world.
	 \param [in,out]	destroyer		 	If non-null, the destroyer.
	 \param [in,out]	mainGameObjectVec	If non-null, the main game object vector.
	 */

	virtual void fire(const sf::Vector2f& pos, 
					  const sf::Vector2f& dirVec,
					  float angle,
					  float power,
					  b2World* world, 
					  ObjectDetroyer* destroyer, 
					  std::list<GameObject*> * mainGameObjectVec) = 0;

	/**
	 \brief	Sets an attacment.
	
	 \param [in,out]	worm	If non-null, the worm.
	 */

	virtual void setAttacment(Worm *worm);

	/**
	 \brief	Gets the weapon.
	
	 \return	null if it fails, else the weapon.
	 */

	virtual Weapon* getWeapon(void) = 0;

	virtual Attachment* getAttachment(void) const{return nullptr;} ;

	/**
	 \brief	Sets a burst.
	
	 \param	burst	The burst.
	 */

	virtual void setBurst(uint8 burst) {m_Burst = burst;}

	sf::Vector2f origenPos; ///< The origen position

	uint8 m_Burst;  ///< The burst

	float m_shotPower;  ///< The shot power

private:

	std::string m_AttachmentName;

	Attachment* m_weaponAttachment;

	


};

/**
// End of Weapon.h
*/

