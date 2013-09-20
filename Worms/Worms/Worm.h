/**
\file	Worm.h

\brief	Declares the worm class.
*/

#pragma once
#include <cmath>
#include <sstream>
#include <string>
#include "EventDispatcher.h"
#include "gameobject.h"
#include "Projectile.h"
#include "External/spine/Animation.h"
#include "External/spine/AnimationState.h"
#include "External/spine/AnimationStateData.h"
#include "External/spine/Atlas.h"
#include "External/spine/AtlasAttachmentLoader.h"
#include "External/spine/Attachment.h"
#include "External/spine/AttachmentLoader.h"
#include "External/spine/Bone.h"
#include "External/spine/BoneData.h"
#include "External/spine/RegionAttachment.h"
#include "External/spine/Skeleton.h"
#include "External/spine/SkeletonData.h"
#include "External/spine/SkeletonJson.h"
#include "External/spine/Skin.h"
#include "External/spine/Slot.h"
#include "External/spine/SlotData.h"
#include "External/spine/spine-sfml.h"
#include "Macros.h"

class Team;
using namespace spine;
/**
\brief	Worm.

\sa	GameObject
\sa	EventListener
*/

class Worm :public GameObject , public EventListener 
{
public:

	/**
	\brief	Values that represent AnimationType.
	*/

	enum AnimationType{EXPLOTION,SLIDE,FREEFALL,IN_MOTION,STATIC};

	/**
	\brief	Values that represent AnimationDirection.
	*/

	enum AnimationDirection{LEFT,RIGHT};

	/**
	\brief	Animation status.
	*/

	struct AnimationStatus
	{
		AnimationDirection direction;
		AnimationType type;
	};

	AnimationStatus m_WormAnimationStatus;  ///< The worm animation status

	/**
	\brief	Initializes a new instance of the Worm class.

	\param [in,out]	world			 	If non-null, the world.
	\param [in,out]	destroyer		 	If non-null, the destroyer.
	\param [in,out]	mainGameObjectVec	If non-null, the main game object vector.
	\param	pos							 	(optional) the position.
	*/

	Worm(b2World* world, ObjectDetroyer* destroyer, std::list<GameObject*>* mainGameObjectVec , Team* myTeam, const  sf::Color& color, sf::Vector2f pos = sf::Vector2f(600.f,1920/2-10.f));

	/**
	\brief	Receive event.

	\param	Event	The event.
	*/

	virtual void receiveEvent(const sf::Event &Event);

	/**
	\brief	Sets an active.

	\param	active	(optional) the active.
	*/

	virtual void setActive(bool active = true);

	/**
	\brief	Finalizes an instance of the Worm class.
	*/

	virtual ~Worm(void)
	{
		killObject(this);
		//getBody()->GetWorld()->DestroyBody(getBody());
		Atlas_dispose(atlas);
		SkeletonData_dispose(skeletonData);
		AnimationStateData_dispose(stateData);
		delete drawable;
		

	}

	/**
	\brief	Updates this object.
	*/

	virtual void update();

	/**
	\brief	Applies the force.

	\param	impulse	The impulse.
	\param	point  	The point.
	*/

	virtual void applyForce(const b2Vec2& impulse, const b2Vec2& point);

	virtual int getHealth(void) const {return m_health;}

	virtual void setWeapon(const std::string &name);

	virtual void clearWeapon(void) ;

	virtual Skeleton* getSkeleton(void) const {return drawable->skeleton;}

	virtual void appayDmg(float dmg){m_health -= dmg;} 

protected:

	/**
	\brief	Draws.

	\param [in,out]	target	Target for the.
	\param	states			  	The states.
	*/

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const ;

private:

	virtual void setSight(void);

	virtual void clearSight(void);

	float m_ShotPower;  ///< The shot power

	int m_health;   ///< The health

	sf::Text m_Pow; ///< The pow

	b2BodyDef m_WormBodyDef;	///< The worm body definition

	b2BodyDef m_UpperBodyDef;   ///< The upper body definition

	b2Body* m_UpperBody;	///< The upper body

	sf::Sprite m_WormSprite;	///< The worm sprite

	b2PolygonShape m_WormShape; ///< The worm shape

	b2CircleShape m_WormFeet;   ///< The worm feet

	b2FixtureDef m_WormFeetFixtureDef;  ///< The worm feet fixture definition

	b2FixtureDef m_WormFixture; ///< The worm fixture

	b2MassData m_massdata;  ///< The massdata

	bool m_walking; ///< true to walking

	b2RevoluteJointDef m_joint; ///< The joint

	//AnimationDB::AnimationsMap* m_AnimationSet;

	sf::IntRect* m_Frame;   ///< The frame

	sf::Sprite m_Sight; ///< The sight

	float m_SightAngle; ///< The sight angle

	sf::Font font;  ///< The font

	Atlas* atlas ;  ///< The atlas
	SkeletonJson* json ;	///< The JSON
	SkeletonData *skeletonData ;	///< Information describing the skeleton

	SkeletonDrawable* drawable; ///< The drawable
	Skeleton* skeleton; ///< The skeleton
	
	AnimationStateData* stateData ; ///< Information describing the state
	bool m_Active;  ///< true to active
	bool flipX; ///< true to flip x coordinate

	sf::Clock m_Clock;  ///< The clock

	sf::Color m_Color;

	/**
	\brief	Loader::AnimationDB* animationDB;

	\param	numToRound	Number of to rounds.
	\param	multiple  	The multiple.

	\return	.
	*/

	int roundUp(int numToRound, int multiple);

	Team* m_MyTeam; ///< my team

};

/**
// End of Worm.h
*/

