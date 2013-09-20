/**
 \file	Projectile.cpp

 \brief	Implements the projectile class.
 */

#include "Projectile.h"
#include "ProjectileCounter.h"
/**
\brief	Initializes a new instance of the Projectile class.

\param [in,out]	world			 	If non-null, the world.
\param [in,out]	destroyer		 	If non-null, the destroyer.
\param [in,out]	mainGameObjectVec	If non-null, the main game object vector.
\param	blastRad				 	(optional) the blast radians.
\param	decayTime				 	(optional) time of the decay.
**/

Projectile::Projectile(b2World* world, ObjectDetroyer* destroyer, std::list<GameObject*>* mainGameObjectVec,float blastRad , float decayTime ):GameObject(destroyer,mainGameObjectVec),m_BlastRadius(blastRad),m_DecayTimeOut(decayTime)
{

	//m_soundBuffer.loadFromFile("Resource/Sound/SFX/explosion3.wav");
	entety.name = typeid(*this).name();
	entety.object = this;
	ballDef.type = b2_dynamicBody;
	ballDef.bullet = true;
	ballDef.position = b2Vec2(0.f,0.f);
	ballDef.userData = (void*)&entety;
	//ballDef.fixedRotation = true;
	setBody(world->CreateBody(&ballDef));



	ballFixtureDef.userData = (void*)&entety;
	ballFixtureDef.filter.categoryBits = GameObject::PROJECTILE;
	ballFixtureDef.filter.maskBits = GameObject::OBJECT | GameObject::PLAYER | GameObject::GROUND;
	
	//massdata.mass = 50000.f;
	//getBody()->SetMassData(&massdata);
	update();
}

/**
 \brief	Gets exponent polygon.

 \return	The exponent polygon.
 */

ClipperLib::Polygons Projectile::getExpPoly(){


	ClipperLib::Polygons expRadius(1);
	for (float i = 0.f; i < 3.141592654f*2.f; i+= 3.141592654f/10.f)
	{
		expRadius[0].push_back(ClipperLib::IntPoint((long long)(m_BlastRadius*cosf(i)*100.f)+m_Cirale.getPosition().x*100.f,(long long)(m_BlastRadius*sinf(i)*100.f)+m_Cirale.getPosition().y*100.f));
	}

	return expRadius;
}


/**
\brief	Updates this object.
**/

void Projectile::update(void){
	if(!entety.dead){
		blastRay.clear();
		if(getBody()->GetWorldCenter().x*100 < -100 || getBody()->GetWorldCenter().y *100 > 2500 ||
			(m_DecayTimeOut > 0.f && m_DecayTimer.getElapsedTime().asMilliseconds() > m_DecayTimeOut)){
				entety.dead = true;
				killObject(this);
		}
		else{
			m_Cirale.setPosition(getBody()->GetWorldCenter().x,getBody()->GetWorldCenter().y);
			m_Cirale.setRotation(getBody()->GetAngle());

		}
	}
}

/**
\brief	Sets a position.

\param	x	The x coordinate.
\param	y	The y coordinate.
**/

void Projectile::setPosition(float x, float y)
{

	getBody()->SetTransform(b2Vec2(x,y),getBody()->GetAngle());

}

/**
\brief	Applies the blast impulse.

\param [in,out]	body	If non-null, the body.
\param	blastCenter 	The blast center.
\param	applyPoint  	The apply point.
\param	blastPower  	The blast power.
**/

void Projectile::applyBlastImpulse(b2Body*body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower)
{
	b2Vec2 blastDir = applyPoint - blastCenter;
	float distance = blastDir.Normalize();
	//ignore bodies exactly at the blast point - blast direction is undefined
	if ( distance == 0 )
		return;
	float invDistance = 1 / distance;
	float impulseMag = blastPower * invDistance * invDistance/1000;

	sf::VertexArray ray(sf::Lines);
	ray.append(sf::Vertex(sf::Vector2f(blastCenter.x,blastCenter.y),sf::Color::Red));
	ray.append(sf::Vertex(sf::Vector2f(applyPoint.x,applyPoint.y),sf::Color::Red));

	GameObject::Entety *bodyEntety = static_cast<GameObject::Entety*>(body->GetUserData());
	bodyEntety->object->applyForce( impulseMag * blastDir, applyPoint );
	//body->ApplyLinearImpulse( impulseMag * blastDir, applyPoint );
}

/**
\brief	Explodes this object.
**/

void Projectile::explode(void)
{

	//m_Sound.play();
	for (int i = 0; i < 100; i++) {
		float angle = (i / (float)100) * 360 * PI/180;
		b2Vec2 rayDir( sinf(angle), cosf(angle) );
		b2Vec2 rayEnd = getBody()->GetWorldCenter() + m_BlastRadius * rayDir;

		//check what this ray hits
		RayCastClosestCallback callback;//basic callback to record body and hit point
		getBody()->GetWorld()->RayCast(&callback, getBody()->GetWorldCenter(), rayEnd);
		if ( callback.m_body && callback.m_body->GetType() == b2_dynamicBody) {


			applyBlastImpulse(callback.m_body, getBody()->GetWorldCenter(), callback.m_point, m_BlastRadius);

		}
		else if (callback.m_body){

			GameObject::Entety *typeA = static_cast<GameObject::Entety*>(callback.m_body->GetUserData());
			if(typeA){
				if(typeA->name == "class Ground"){
					Ground *ground = dynamic_cast<Ground*>(typeA->object);
					ground->setClipOffPoly(getExpPoly());
				}
			}

		}
	}
}

/**
// End of Projectile.cpp
 */

