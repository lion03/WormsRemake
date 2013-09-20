/**
\file	Uzi.cpp

\brief	Implements the uzi class.
*/

#include "Uzi.h"
#include "Bullet.h"
#include "ResourceManager.h"

/**
\brief	Initializes a new instance of the Uzi class.
*/

Uzi::Uzi(void):Weapon("uzi",0)
{


	m_fireSoundBuff = ResourceManager<sf::SoundBuffer>::getInstence()->getResource("uziFire");
	m_fireSound.setBuffer(*m_fireSoundBuff.get());

}

/**
\brief	Finalizes an instance of the Uzi class.
*/
Uzi::~Uzi(void)
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

void Uzi::fire(const sf::Vector2f&pos, const sf::Vector2f&dirVec, float angle, float power, b2World*world, ObjectDetroyer*destroyer, std::list<GameObject*>*mainGameObjectVec)
{

	if(m_Burst >= 10)
		m_fireSound.play();

	if(m_Burst > 0 && m_RateClock.getElapsedTime().asMilliseconds() > 10){


		int randomSprade = rand()%5;
		int sprade = -5 +randomSprade;

		angle += DEG_TO_RAD(sprade);
		//Projectile* shot = 
		//shot->setPosition(pos.x,pos.y);



		mainGameObjectVec->push_back(new Bullet(world,destroyer,mainGameObjectVec,500.f));

		mainGameObjectVec->back()->getBody()->SetTransform(b2Vec2(pos.x,pos.y),angle);


		mainGameObjectVec->back()->getBody()->SetLinearVelocity(mainGameObjectVec->back()->getBody()->GetWorldVector(b2Vec2(20.f,0.f)));


		--m_Burst;
		m_RateClock.restart();
	}


}

/**
// End of Uzi.cpp
 */

