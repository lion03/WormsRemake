/**
\file	Projectile.h

\brief	Declares the projectile class.
*/

#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "gameobject.h"
#include "External/Clipper/clipper.hpp"
#include "ResourceManager.h"
#include "Ground.h"
#include "ProjectileCounter.h"

#define PI  3.1415926535897932384626433f

/**
\brief	Projectile.

\sa	GameObject
*/

class Projectile :public GameObject
{
public:

	/**
	\brief	Initializes a new instance of the Projectile class.

	\param [in,out]	world			 	If non-null, the world.
	\param [in,out]	destroyer		 	If non-null, the destroyer.
	\param [in,out]	mainGameObjectVec	If non-null, the main game object vector.
	\param	blastRad				 	(optional) the blast radians.
	\param	decayTime				 	(optional) time of the decay.
	**/

	Projectile(b2World* world, ObjectDetroyer* destroyer, std::list<GameObject*>* mainGameObjectVec,float blastRad = 1.f, float decayTime = 0.f);

	/**
	\brief	Gets exponent polygon.

	\return	The exponent polygon.
	*/

	ClipperLib::Polygons getExpPoly();

	/**
	\brief	Updates this object.
	*/

	virtual void update();

	/**
	\brief	Sets a position.

	\param	x	The x coordinate.
	\param	y	The y coordinate.
	*/

	virtual void setPosition(float x,float y);

	/**
	\brief	Finalizes an instance of the Projectile class.
	*/

	virtual ~Projectile(void)
	{
		ProjectileCounter::getInstance().removeProjectile();
		//getBody()->GetWorld()->DestroyBody(getBody());

	}

	/**
	\brief	Applies the blast impulse.

	\param [in,out]	body	If non-null, the body.
	\param	blastCenter			The blast center.
	\param	applyPoint			The apply point.
	\param	blastPower			The blast power.
	*/

	void applyBlastImpulse(b2Body* body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower);

	/**
	\brief	Applies the force.

	\param	impulse	The impulse.
	\param	point  	The point.
	*/

	virtual void applyForce(const b2Vec2& impulse, const b2Vec2& point){}

	/**
	\brief	Gets blast radius.

	\return	The blast radius.
	*/

	virtual float getBlastRadius() const {return m_BlastRadius;}

	/**
	\brief	Sets blast radius.

	\param	blastRadius	The blast radius.
	*/

	virtual void setBlastRadius(float blastRadius){m_BlastRadius = blastRadius;}

	/**
	\brief	Explodes this object.
	*/

	virtual void explode();

protected:

	/**
	\brief	Draws.

	\param [in,out]	target	Target for the.
	\param	states			  	The states.
	*/

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {

		target.draw(m_Cirale,states);
		target.draw(blastRay,states);


	}

	sf::CircleShape m_Cirale;   ///< The cirale

	b2FixtureDef ballFixtureDef;	///< The ball fixture definition

	b2BodyDef ballDef;  ///< The ball definition

	b2CircleShape ballShape;	///< The ball shape

	b2MassData massdata;	///< The massdata

	float m_BlastRadius;	///< The blast radius

	/**
	\brief	Ray cast closest callback.

	\sa	b2RayCastCallback
	*/

	class RayCastClosestCallback : public b2RayCastCallback
	{
	public:
		b2Body* m_body; ///< The body
		b2Vec2 m_point; ///< The point

		/**
		\brief	Initializes a new instance of the RayCastClosestCallback class.
		*/

		RayCastClosestCallback() { m_body = NULL; }

		/**
		\brief	Reports a fixture.

		\param [in,out]	fixture	If non-null, the fixture.
		\param	point			   	The point.
		\param	normal			   	The normal.
		\param	fraction		   	The fraction.

		\return	.
		*/

		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
		{
			m_body = fixture->GetBody();
			m_point = point;
			return fraction;
		}
	};

private:














	int m_RayNums;  ///< The ray nums

	sf::VertexArray blastRay;   ///< The blast ray

	std::shared_ptr<sf::SoundBuffer> m_soundBuffer;  ///< Buffer for sound data

	sf::Clock m_DecayTimer;

	sf::Sound m_Sound;  ///< The sound

	float m_DecayTimeOut;
};

/**
// End of Projectile.h
*/

