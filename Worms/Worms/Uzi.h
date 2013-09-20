/**
\file	Uzi.h

\brief	Declares the uzi class.
*/

#pragma once
#include "Macros.h"
#include "weapon.h"

/**
\brief	Uzi.

\sa	Weapon
*/

class Uzi :
	public Weapon
{
public:

	/**
	\brief	Initializes a new instance of the Uzi class.
	*/

	Uzi(void);

	/**
	\brief	Finalizes an instance of the Uzi class.
	*/

	virtual ~Uzi(void);

	/**
	\brief	Gets the weapon.

	\return	null if it fails, else the weapon.
	*/

	virtual Weapon* getWeapon(void) {return this;}

	/**
	\brief	Fire shot.

	\param	power	The power.
	*/

	virtual void fireShot(float power){			
		

		if(m_Burst<=0){
			
			m_Burst = 10;
			m_RateClock.restart();
		}
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
		std::list<GameObject*> * mainGameObjectVec);

private:

	sf::Clock m_RateClock;  ///< The rate clock

	std::shared_ptr<sf::SoundBuffer> m_fireSoundBuff;
	sf::Sound m_fireSound;
};

