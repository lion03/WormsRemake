/**
\file	Shotgun.h

\brief	Declares the shotgun class.
*/

#pragma once
#include "weapon.h"
#include "Macros.h"
#include "Bullet.h"
/**
\brief	Shotgun.

\sa	Weapon
*/

class Shotgun :
	public Weapon
{
public:

	/**
	\brief	Initializes a new instance of the Shotgun class.
	*/

	Shotgun(void);

	/**
	\brief	Finalizes an instance of the Shotgun class.
	*/

	virtual ~Shotgun(void);

	/**
	\brief	Gets the weapon.

	\return	null if it fails, else the weapon.
	*/

	virtual Weapon* getWeapon(void) {return this;}

	virtual void loadShot(){

		if(m_Burst<=0 &&  !m_loaded){
			m_LoadSound.play();
			m_loaded = true;
		}
	}
	/**
	\brief	Fire shot.

	\param	power	The power.
	*/

	virtual void fireShot(float power){

		if(m_Burst<=0){
			ProjectileCounter::getInstance().addProjecile(5);

			m_Burst = 1;
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
		std::list<GameObject*>* mainGameObjectVec);

private:

	std::shared_ptr<sf::SoundBuffer> m_loadSoundBuff;

	std::shared_ptr<sf::SoundBuffer> m_fireSoundBuff;

	sf::Sound m_LoadSound;

	sf::Sound m_fireSound;

	bool m_loaded;
};

