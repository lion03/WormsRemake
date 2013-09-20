/**
 \file	Bullet.cpp

 \brief	Implements the bullet class.
 */

#include "Bullet.h"

/**
 \brief	Initializes a new instance of the Bullet class.

 \param [in,out]	world			 	If non-null, the world.
 \param [in,out]	destroyer		 	If non-null, the destroyer.
 \param [in,out]	mainGameObjectVec	If non-null, the main game object vector.
 \param	decayTime					 	Time of the decay.
 */

Bullet::Bullet(b2World* world, ObjectDetroyer* destroyer, std::list<GameObject*>* mainGameObjectVec, float decayTime):Projectile(world,destroyer,mainGameObjectVec,0.5f ,decayTime)
{



	m_Cirale.setRadius(0.01f);
	m_Cirale.setOrigin(0.01f,0.01f);
	ballFixtureDef.density = 10.f;
	ballShape.m_radius = 0.01f;
	ballFixtureDef.isSensor = false;
	ballFixtureDef.shape = &ballShape;
	
	getBody()->SetBullet(true);
	getBody()->CreateFixture(&ballFixtureDef);
	massdata.center = getBody()->GetPosition();
	m_BlastRadius = 0.35f;

}

/**
 \brief	Finalizes an instance of the Bullet class.
 */

Bullet::~Bullet()
{
}

/**
\brief	Applies the blast impulse.

\param [in,out]	body	If non-null, the body.
\param	blastCenter 	The blast center.
\param	applyPoint  	The apply point.
\param	blastPower  	The blast power.
**/

void Bullet::applyBlastImpulse(b2Body*body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower)
{

	GameObject::Entety *bodyEntety = static_cast<GameObject::Entety*>(body->GetUserData());
	bodyEntety->object->applyForce( b2Vec2(), applyPoint );
}

/**
\brief	Explodes this object.
**/

void Bullet::explode(){

	auto contact = getBody()->GetContactList();

	while (contact)
	{
		GameObject::Entety *typeA = static_cast<GameObject::Entety*>((contact->contact->GetFixtureA()->GetUserData()));

		if(typeA){
			if(typeA->name == "class Ground"){
				Ground *ground = dynamic_cast<Ground*>(typeA->object);
				ground->setClipOffPoly(getExpPoly());
			}
			else if(typeA->name == "class Worm")
			{
				typeA->object->appayDmg(1);
			}
		}

		GameObject::Entety *typeB = static_cast<GameObject::Entety*>((contact->contact->GetFixtureB()->GetUserData()));
		if(typeB){
			if(typeA->name == "class Ground"){
				Ground *ground = dynamic_cast<Ground*>(typeA->object);
				ground->setClipOffPoly(getExpPoly());
			}
			else if(typeB->name == "class Worm")
			{
				typeB->object->appayDmg(1);
			}
		}

		contact = contact->next;

	}
	//bodyEntety->object->applyForce( b2Vec2(), applyPoint );

}

/**
// End of Bullet.cpp
 */

