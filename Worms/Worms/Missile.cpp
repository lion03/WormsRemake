/**
 \file	Missile.cpp

 \brief	Implements the missile class.
 */

#include "Missile.h"

/**
 \brief	Initializes a new instance of the Missile class.

 \param [in,out]	world			 	If non-null, the world.
 \param [in,out]	destroyer		 	If non-null, the destroyer.
 \param [in,out]	mainGameObjectVec	If non-null, the main game object vector.
 \param	blastRad					 	The blast radians.
 */

Missile::Missile(b2World* world, ObjectDetroyer* destroyer, std::list<GameObject*>* mainGameObjectVec, float blastRad):Projectile(world,destroyer,mainGameObjectVec,blastRad,10000.f)
{

	m_Cirale.setRadius(0.05f);
	m_Cirale.setOrigin(0.05f,0.05f);
	ballFixtureDef.density = 10.f;
	ballShape.m_radius = 0.1f;
	ballFixtureDef.isSensor = true;
	ballFixtureDef.shape = &ballShape;
	getBody()->SetBullet(true);
	getBody()->CreateFixture(&ballFixtureDef);
	massdata.center = getBody()->GetPosition();
	m_BlastRadius = 0.75f;

	m_expSoundBuff = ResourceManager<sf::SoundBuffer>::getInstence()->getResource("bazookaExp");
	m_expSound.setBuffer(*m_expSoundBuff.get());
}

/**
// End of Missile.cpp
 */

