#pragma once
#include "Projectile.h"

class Bullet : public Projectile
{
public:
	Bullet(b2World* world, ObjectDetroyer* destroyer, std::list<GameObject*>* mainGameObjectVec, float decayTime = 0.f);

	~Bullet();


	virtual void applyBlastImpulse(b2Body* body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower);


	virtual void explode();

private:

};

