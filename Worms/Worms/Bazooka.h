/**
 \file	Bazooka.h

 \brief	Declares the bazooka class.
 */

#pragma once
#include "Weapon.h"

/**
 \brief	Bazooka.

 \sa	Weapon
 */

class Bazooka :
	public Weapon
{
public:

	/**
	 \brief	Initializes a new instance of the Bazooka class.
	 */

	Bazooka(void);

	/**
	 \brief	Finalizes an instance of the Bazooka class.
	 */

	virtual ~Bazooka(void);

	/**
	 \brief	Gets the weapon.
	
	 \return	null if it fails, else the weapon.
	 */

	virtual Weapon* getWeapon(void) {return this;}

	/**
	 \brief	Fire shot.
	
	 \param	power	The power.
	 */

	virtual void fireShot(float power) {
		ProjectileCounter::getInstance().addProjecile();
		m_Burst = 1; 
		m_shotPower = power;
	}

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
					  std::list<GameObject*>* mainGameObjectVec);

private:

	std::shared_ptr<sf::SoundBuffer> m_lunchSoundBuff;
	sf::Sound m_lunchSound;
};

/**
// End of Bazooka.h
 */

