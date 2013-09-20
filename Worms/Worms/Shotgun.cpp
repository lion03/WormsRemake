/**
\file	Shotgun.cpp

\brief	Implements the shotgun class.
*/

#include "Shotgun.h"
#include "ResourceManager.h"

/**
\brief	Initializes a new instance of the Shotgun class.
*/

Shotgun::Shotgun(void):Weapon("shotgun"),m_loaded(false)
{
	/**
	\brief	Finalizes an instance of the Shotgun class.
	*/
	m_fireSoundBuff = ResourceManager<sf::SoundBuffer>::getInstence()->getResource("shotGunFire");
	m_loadSoundBuff =  ResourceManager<sf::SoundBuffer>::getInstence()->getResource("shotGunLoad");
	m_LoadSound.setBuffer(*m_loadSoundBuff.get());
	m_fireSound.setBuffer(*m_fireSoundBuff.get());

}

/**
 \brief	Finalizes an instance of the Shotgun class.
 */

Shotgun::~Shotgun(void)
{
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

void Shotgun::fire(const sf::Vector2f&pos, const sf::Vector2f&dirVec, float angle, float power, b2World*world, ObjectDetroyer*destroyer, std::list<GameObject*>*mainGameObjectVec)
{

	if(m_Burst > 0){
		m_fireSound.play();
		float sprade = RAD_TO_DEG(angle) - 15.f;
		for (int i = 0; i < 5; i++)
		{
			mainGameObjectVec->push_back(new Bullet(world,destroyer,mainGameObjectVec,200.f));


			mainGameObjectVec->back()->getBody()->SetTransform(b2Vec2(pos.x,pos.y),DEG_TO_RAD(sprade));

			mainGameObjectVec->back()->getBody()->SetLinearVelocity(mainGameObjectVec->back()->getBody()->GetWorldVector(b2Vec2(20.f,0.f)));

			sprade += 6.f;
		}

		--m_Burst;
		m_loaded = false;
	}

}

/**
// End of Shotgun.cpp
 */

