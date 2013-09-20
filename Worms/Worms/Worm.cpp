/**
\file	Worm.cpp

\brief	Implements the worm class.
*/

#include "Worm.h"
#include "Team.h"
#include "Weapon.h"

/**
\brief	Initializes a new instance of the Worm class.

\param [in,out]	world			 	If non-null, the world.
\param [in,out]	destroyer		 	If non-null, the destroyer.
\param [in,out]	mainGameObjectVec	If non-null, the main game object vector.
\param [in,out]	myTeam			 	If non-null, my team.
\param	color						 	The color.
\param	pos							 	The position.
*/

Worm::Worm(b2World*world, ObjectDetroyer*destroyer, std::list<GameObject*>*mainGameObjectVec, Team* myTeam, const  sf::Color& color,sf::Vector2f pos ):
	GameObject(destroyer,mainGameObjectVec),
	m_Active(false),
	m_health(100),
	flipX(false),
	m_MyTeam(myTeam),
	m_Color(color)
{

	//game object init
	{
		entety.name = typeid(*this).name();

		entety.object = (this); 
	}


	font.loadFromFile("ariblk.ttf");

	m_Pow.setFont(font);

	m_ShotPower = 0.f;
	
	m_SightAngle = 0.f;

	//box2d init
	{
		m_WormBodyDef.position = b2Vec2(pos.x/100.f,pos.y/100.f);

		m_WormBodyDef.fixedRotation = true;

		m_WormShape.SetAsBox(0.045f,0.045f);

		m_WormFeetFixtureDef.friction = 5.f;

		m_WormFeet.m_radius = 0.045f;//m_Frame->width/2;

		m_WormFeet.m_p = b2Vec2(0, 0.045f);

		m_WormBodyDef.type = b2_dynamicBody;

		setBody(world->CreateBody(&m_WormBodyDef));

		getBody()->GetContactList();

		sf::FloatRect base;

		assert(m_Frame);

		m_WormFixture.userData = (void*)&entety;

		m_WormFeetFixtureDef.userData = (void*)&entety;

		m_WormFixture.shape = &m_WormShape;

		m_WormFeetFixtureDef.shape = &m_WormFeet;

		m_WormFixture.friction= 1.f;

		m_WormFixture.density = 1.75f;

		m_WormFeetFixtureDef.friction = 1.f;

		m_WormFeetFixtureDef.density = 1.75f;

		m_UpperBodyDef.position =  b2Vec2(pos.x/100.f,pos.y/100.f);

		m_UpperBodyDef.fixedRotation = true;

		m_UpperBodyDef.type = b2_dynamicBody;

		m_UpperBodyDef.angularDamping = 0.9f;

		m_WormFixture.filter.categoryBits = GameObject::PLAYER;

		m_WormFixture.filter.maskBits = GameObject::OBJECT | GameObject::PLAYER | GameObject::GROUND | GameObject::PROJECTILE;

		m_WormFeetFixtureDef.filter.categoryBits = GameObject::PLAYER;

		m_WormFeetFixtureDef.filter.maskBits = GameObject::OBJECT | GameObject::PLAYER | GameObject::GROUND | GameObject::PROJECTILE;

		getBody()->CreateFixture(&m_WormFixture);

		getBody()->CreateFixture(&m_WormFeetFixtureDef);

		getBody()->SetUserData((void*)&entety);

		getBody()->SetAngularDamping(0.9f); 
	}


	//Skeletal animation init
	{
		atlas = Atlas_readAtlasFile("data/WormAtlas.atlas");

		json = SkeletonJson_create(atlas);

		json->scale = 0.01f;
		skeletonData = SkeletonJson_readSkeletonDataFile(json,"data/worm2.json"); // TODO:delete skeletonData in dtor

		SkeletonJson_dispose(json);

		stateData = AnimationStateData_create(skeletonData);

		drawable = new SkeletonDrawable(skeletonData, stateData);  // TODO: delete in dtor 
	}


	m_Pow.setColor(m_Color);

	m_Pow.scale(0.01,0.01);

	AnimationState_setAnimationByName(drawable->state, "idle", false);

}

/**
\brief	Receive event.

\param	Event	The event.
*/

void Worm::receiveEvent(const sf::Event &Event){

	if(m_Active){

		if(Event.type == sf::Event::KeyPressed || Event.type == sf::Event::KeyReleased){

			switch (Event.key.code){

			case sf::Keyboard::Left:
				if(Event.type == sf::Event::KeyPressed){

					if(getBody()->GetLinearVelocity().LengthSquared() < 1.5f){

						getBody()->ApplyForceToCenter(b2Vec2(-1.f,0));

						if(AnimationState_isComplete(drawable->state))

							AnimationState_setAnimationByName(drawable->state,"walk",false);

						flipX = false;

						m_WormAnimationStatus.type = IN_MOTION;
					}
				}
				else if(Event.type == sf::Event::KeyReleased){

					AnimationState_setAnimationByName(drawable->state,"idle",false);

					m_WormAnimationStatus.type = STATIC;
				}

				break;
			case sf::Keyboard::Right:

				if(Event.type == sf::Event::KeyPressed){

					if(getBody()->GetLinearVelocity().LengthSquared() < 1.5f){

						if(AnimationState_isComplete(drawable->state))

							AnimationState_setAnimationByName(drawable->state,"walk",false);

						getBody()->ApplyForceToCenter(b2Vec2(1.f,0));

						flipX = true;

						m_WormAnimationStatus.type = IN_MOTION;
					}
				}
				else if(Event.type == sf::Event::KeyReleased){

					AnimationState_setAnimationByName(drawable->state,"idle",false);

					m_WormAnimationStatus.type = STATIC;

				}

				break;

			case sf::Keyboard::Up:

				m_SightAngle += b2_pi/60;

				break;

			case sf::Keyboard::Down:

				m_SightAngle -= b2_pi/60;

				break;

			case sf::Keyboard::Space:

				if(Event.type == sf::Event::KeyReleased){

					m_MyTeam->getWeapon()->fireShot(m_ShotPower);

					m_ShotPower = 0.f;

				}
				else if(Event.type == sf::Event::KeyPressed){

					m_MyTeam->getWeapon()->loadShot();

					if(m_ShotPower<20.f)

						m_ShotPower+= 0.5;
				}
				break;
			case sf::Keyboard::R:

				break;
			case sf::Keyboard::T:
				break;

			case sf::Keyboard::LShift:

			case sf::Keyboard::RShift:
				if(getBody()->GetLinearVelocity().LengthSquared() < 0.1f){

					getBody()->ApplyForceToCenter(b2Vec2(flipX?  0.5f : -0.5f,-1.5f));

					AnimationState_setAnimationByName(drawable->state,"jump",false);
				}
			default:
				break;
			}
		}
	}
}

/**
\brief	Updates this object.
*/

void Worm::update(void)
{

	if(m_health > 0){

		float delta = m_Clock.getElapsedTime().asSeconds();

		m_Clock.restart();

		drawable->update(delta);

		m_Pow.setString(std::to_string((long long)m_health));

		b2Vec2 pos = getBody()->GetPosition();

		float32 Angle = getBody()->GetAngle();

		b2Vec2 velocity = getBody()->GetLinearVelocity();

		float32 x = (getBody()->GetPosition().x);

		float32 y = (getBody()->GetPosition().y)+ 0.09f;

		float32 r = (getBody()->GetAngle()*(180/b2_pi));

		BoneData* rightBone = SkeletonData_findBone(drawable->skeleton->data,"shoulder");

		rightBone->rotation = m_SightAngle*180/b2_pi;

		m_WormSprite.setRotation(180-atan2f(getBody()->GetLinearVelocity().y,getBody()->GetLinearVelocity().x)*180/b2_pi);

		skeleton = drawable->skeleton;

		skeleton->flipX = flipX;

		if(m_Active){

			auto wep = m_MyTeam->getWeapon();

			wep->setAttacment(this);

			setSight();

		}
		else
		{
			clearWeapon();
			clearSight();
		}
		if(flipX){
			skeleton->root->x = -x;
			skeleton->root->y = -y;
		}
		else{
			skeleton->root->x = x;
			skeleton->root->y = y;
		}

		Skeleton_updateWorldTransform(drawable->skeleton);
		if(skeleton->root->worldX < 0 || skeleton->root->worldX > 25.6 ||
			skeleton->root->worldY > 19.2){

				m_health = 0;
				if(m_Active){
					m_MyTeam->setSuicid();
					return;
				}

		}

		m_Sight.setPosition(skeleton->root->x +30.f* cosf(-m_SightAngle),skeleton->root->y +30.f*sinf(-m_SightAngle));

		if(m_Active){

			auto sightBone = Skeleton_findBone(drawable->skeleton,"sight");

			float angle = atan2f( sightBone->worldY , sightBone->worldX);

			auto shoulderBone = Skeleton_findBone(drawable->skeleton,"shoulder");

			m_MyTeam->getWeapon()->fire(sf::Vector2f(sightBone->worldX, sightBone->worldY),sf::Vector2f(), flipX ? m_SightAngle :  b2_pi - m_SightAngle ,m_ShotPower,getBody()->GetWorld(),m_Destroyer,m_MainObjectVec);

		}

		if(velocity.LengthSquared() > 1.0){



		}
		if(!getBody()->GetContactList()){

			float angel =  atan2f(getBody()->GetLinearVelocity().y,getBody()->GetLinearVelocity().x)*180/b2_pi;

			angel = roundUp((int)angel,6);

			while (angel< 0.f)
				angel+=360.f;

			while(angel >= 359.f)
				angel -= 360.f;

		}
		else{

		}

		m_Pow.setPosition((skeleton->root->worldX),(skeleton->root->worldY-1));
	}
}

/**
\brief	Applies the force.

\param	impulse	The impulse.
\param	point  	The point.
*/

void Worm::applyForce(const b2Vec2&impulse, const b2Vec2&point)
{

	m_WormAnimationStatus.type = EXPLOTION;

	getBody()->ApplyLinearImpulse(impulse,point);

	AnimationState_setAnimationByName(drawable->state, "exp", false);

	float32 x = (getBody()->GetPosition().x);

	float32 y = (getBody()->GetPosition().y);

	skeleton = drawable->skeleton;

	if(flipX){
		skeleton->root->x = -x;
		skeleton->root->y = -y;
	}
	else{
		skeleton->root->x = x;
		skeleton->root->y = y;
	}
	Skeleton_updateWorldTransform(skeleton);

}

/**
\brief	Draws.

\param [in,out]	target	Target for the.
\param	states			  	The states.
*/

void Worm::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

	if(m_health>0){
		target.draw(m_WormSprite);

		target.draw(*drawable,states);

		target.draw(m_Pow,states);
	}
}

/**
\brief	Round up.

\param	numToRound	Number of to rounds.
\param	multiple  	The multiple.

\return	.
*/

int Worm::roundUp(int numToRound, int multiple)	{
	if(multiple == 0)
	{
		return 0;
	}
	return ((numToRound - 1) / multiple + 1) * multiple;  
}

/**
\brief	Sets a weapon.

\param	name	The name.
*/

void Worm::setWeapon(const std::string &name)
{
	if(name != "")
		Skeleton_setAttachment(drawable->skeleton,"arm item",name.c_str());
	else{

		clearWeapon();
	}
}

/**
\brief	Clears the weapon.
*/

void Worm::clearWeapon(void)
{
	auto slot = Skeleton_findSlot(drawable->skeleton,"arm item");

	Slot_setAttachment(slot,NULL);

}

/**
\brief	Clears the sight.
*/

void Worm::clearSight(void)
{
	auto slot = Skeleton_findSlot(drawable->skeleton,"sightAttach");

	Slot_setAttachment(slot,NULL);
}

/**
\brief	Sets the sight.
*/

void Worm::setSight(void)
{
	Skeleton_setAttachment(drawable->skeleton,"sightAttach","sight");
}

/**
\brief	Sets an active.

\param	active	(optional) the active.
*/

void Worm::setActive(bool active) {

	m_Active=active; 

}

