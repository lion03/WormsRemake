/**
\file	Bazooka.cpp

\brief	Implements the bazooka class.
*/

#include "Bazooka.h"
#include "Missile.h"
/**
\brief	Initializes a new instance of the Bazooka class.
*/

Bazooka::Bazooka(void):Weapon("bazooka")
{
	/**
	\brief	Finalizes an instance of the Bazooka class.
	*/

	m_lunchSoundBuff = ResourceManager<sf::SoundBuffer>::getInstence()->getResource("bazookaFire");

	m_lunchSound.setBuffer(*m_lunchSoundBuff.get());

}

/**
 \brief	Finalizes an instance of the Bazooka class.
 */

Bazooka::~Bazooka(void)
{
}

/**
\brief	Fires.

\param	pos							 	The position.
\param	dirVec						 	The sf vector 2f.
\param	angle						 	The angle.
\param	power						 	The power.
\param [in,out]	world			 	If non-null, the world.
\param [in,out]	destroyer		 	If non-null, the destroyer.
\param [in,out]	mainGameObjectVec	If non-null, the main game object vector.
*/

void Bazooka::fire(const sf::Vector2f&pos, const sf::Vector2f& dirVec, float angle, float power, b2World*world, ObjectDetroyer*destroyer, std::list<GameObject*>*mainGameObjectVec)
{

	if(m_Burst > 0){

		m_lunchSound.play();

		mainGameObjectVec->push_back(new Missile(world,destroyer,mainGameObjectVec,0.5f));

		mainGameObjectVec->back()->getBody()->SetTransform(b2Vec2(pos.x,pos.y),angle);

		mainGameObjectVec->back()->getBody()->SetLinearVelocity(mainGameObjectVec->back()->getBody()->GetWorldVector(b2Vec2(m_shotPower,0.f)));

		m_Burst = 0; 
	}
}

/**
// End of Bazooka.cpp
 */

