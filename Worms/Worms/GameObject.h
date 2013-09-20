/**
\file	GameObject.h

\brief	Declares the game object class.
*/

#pragma once
#include <set>
#include <SFML/Graphics.hpp>
#include <vector>
#include "ObjectDetroyer.h"

/**
\brief	Game object.

\sa	sf::Drawable
*/

class GameObject : public sf::Drawable
{
public:

	/**
	\brief	Values that represent _entityCategory.
	*/

	enum _entityCategory {
		BOUNDARY =          0x0001,
		PLAYER =     0x0002,
		PROJECTILE =        0x0004,
		GROUND = 0x0008,
		OBJECT =    0x0010,
	};

	/**
	\brief	Initializes a new instance of the GameObject class.

	\param [in,out]	objectDetroyer   	If non-null, the object detroyer.
	\param [in,out]	mainGameObjectVec	If non-null, the main game object vector.
	*/

	GameObject(ObjectDetroyer* objectDetroyer, std::list<GameObject*>* mainGameObjectVec):m_Destroyer(objectDetroyer),m_MainObjectVec(mainGameObjectVec)
	{
		entety.dead = false;
	}

	/**
	\brief	Updates this object.
	*/

	virtual void update() = 0;

	/**
	\brief	Finalizes an instance of the GameObject class.
	*/

	virtual ~GameObject(void)
	{

		m_body->GetWorld()->DestroyBody(m_body);

		m_MainObjectVec->remove(this);

	}

	/**
	\brief	Entety.
	*/

	struct Entety{
		GameObject* object;
		std::string name;
		bool dead;
	};

	Entety entety;  ///< The entety

	/**
	\brief	Gets the body.

	\return	null if it fails, else the body.
	*/

	b2Body* getBody(){return m_body;}

	/**
	\brief	Sets a body.

	\param [in,out]	body	If non-null, the body.
	*/

	virtual void setBody(b2Body* body){m_body = body;}

	/**
	\brief	Kill object.

	\param [in,out]	gameObject	If non-null, the game object.
	*/

	void killObject(GameObject *gameObject){
		m_Destroyer->addObjectToKillList(gameObject);
	}

	/**
	\brief	Gets mass data.

	\return	null if it fails, else the mass data.
	*/

	//b2MassData* getMassData(void) const {b2MassData data; m_body->GetMassData(&data); return &data;}

	/**
	\brief	Gets body position.

	\return	The body position.
	*/

	b2Vec2 getBodyPos(void) const {return m_body->GetPosition();}

	/**
	\brief	Gets body angle.

	\return	The body angle.
	*/

	float32 getBodyAngle(void) const {return m_body->GetAngle();}

	virtual void setPosition(float x,float y){}

	/**
	\brief	Applies the force.

	\param	impulse	The impulse.
	\param	point  	The point.
	*/

	virtual void applyForce(const b2Vec2& impulse, const b2Vec2& point) = 0;

	virtual void appayDmg(float dmg){}



protected:

	/**
	\brief	Draws.

	\param [in,out]	target	Target for the.
	\param	states			  	The states.
	*/

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;

	b2Body* m_body; ///< The body

	ObjectDetroyer* m_Destroyer;	///< The destroyer

	std::list<GameObject*>* m_MainObjectVec;  ///< The main object vector

private:



};

/**
// End of GameObject.h
*/

