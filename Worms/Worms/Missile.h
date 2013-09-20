#pragma once
#include "Projectile.h"

class Missile : public Projectile{


public:

	Missile(b2World* world, ObjectDetroyer* destroyer, std::list<GameObject*>* mainGameObjectVec, float blastRad);

	virtual ~Missile(void) {}

	virtual void explode(){

		m_expSound.play();


		for (int i = 0; i < 100; i++) {
			float angle = (i / (float)100) * 360 * PI/180;
			b2Vec2 rayDir( sinf(angle), cosf(angle) );
			b2Vec2 rayEnd = getBody()->GetWorldCenter() + m_BlastRadius * rayDir;

			//check what this ray hits
			RayCastClosestCallback callback;//basic callback to record body and hit point
			getBody()->GetWorld()->RayCast(&callback, getBody()->GetWorldCenter(), rayEnd);
			if ( callback.m_body && callback.m_body->GetType() == b2_dynamicBody) {

				GameObject::Entety *typeA = static_cast<GameObject::Entety*>(callback.m_body->GetUserData());
				applyBlastImpulse(callback.m_body, getBody()->GetWorldCenter(), callback.m_point, m_BlastRadius/callback.m_point.LengthSquared()*10);
				typeA->object->appayDmg(callback.m_point.LengthSquared()/100);

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

		Projectile::explode();

	}

private:

	std::shared_ptr<sf::SoundBuffer> m_expSoundBuff;

	sf::Sound m_expSound;

};

