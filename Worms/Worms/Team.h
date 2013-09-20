/**
\file	Team.h

\brief	Declares the team class.
*/

#pragma once
#include <vector>
#include "EventDispatcher.h"
#include "Worm.h"


class Weapon;
class Arsenal;
/**
\brief	Team.

\sa	GameObject
\sa	EventListener
*/

class Team : public EventListener ,public sf::Drawable
{
public:

	/**
	\brief	Initializes a new instance of the Team class.

	\param [in,out]	world			 	If non-null, the world.
	\param [in,out]	objectDetroyer   	If non-null, the object detroyer.
	\param [in,out]	mainGameObjectVec	If non-null, the main game object vector.
	\param	teamSize					 	Size of the team.
	\param	teamColor					 	The team color.
	*/

	Team(b2World* world, ObjectDetroyer* objectDetroyer, std::list<GameObject*> * mainGameObjectVec , uint8 teamSize, const sf::Color& teamColor = sf::Color::White);

	/**
	\brief	Finalizes an instance of the Team class.
	*/

	virtual ~Team(void);

	/**
	\brief	Receive event.

	\param	Event	The event.
	*/

	virtual void receiveEvent(const sf::Event& Event);

	/**
	\brief	virtual void setWeapon(Weapon* weapon){m_ActiveWeapon = weapon;}

	\param	weapon	The weapon.
	*/

	virtual void setWeapon1(std::string weapon){m_WeaponName = weapon;}
	virtual void setWeapon(Weapon* weapon){m_ActiveWeapon = weapon;}

	/**
	\brief	Gets the weapon.

	\return	The weapon.
	*/



	virtual Weapon* getWeapon(void) const {return m_ActiveWeapon;} 

	virtual void setActive(bool active = true);

	virtual bool getActive(void)const;

	Worm* getActiveWorm(void) const {return *m_AliveWormIterator;}


	//Worm* getActiveWorm(void) const {return m_TeamMembers[index];}

	virtual unsigned int getTeamHealth(void) ;

	virtual bool isDead(void) const {return m_isDead;}

	virtual void setSuicid(bool suicid = true) {m_suicid = suicid;}

	virtual bool getSuicid(void){
	
		bool temp = m_suicid;

		m_suicid = false;

		return temp;
	}


protected:

	/**
	\brief	Draws.

	\param [in,out]	target	Target for the.
	\param	states			  	The states.
	*/

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	Worm* m_ActiveWorm;

	uint8 m_TeamSize;   ///< Size of the team

	bool m_Active;  ///< true to active

	std::vector<Worm*> m_TeamMembers;   ///< The team members

	typedef std::vector<Worm>::iterator wormIterator;

	wormIterator m_WormIterator;

	ObjectDetroyer* m_PtrToObjDestroyer;	///< The pointer to object destroyer

	std::list<GameObject*>* m_PtrToMainGameObjVec;	///< The pointer to main game object vector

	Weapon* m_ActiveWeapon; ///< The active weapon

	Arsenal* m_TeamArsenal; ///< The team arsenal

	sf::Text m_TotalHealth; ///< The total health

	std::string m_WeaponName;   ///< Name of the weapon

	unsigned int index;  ///< Zero-based index of the 

	sf::Color m_TeamColor;  ///< The team color

	std::list<Worm*> m_AliveWorms;

	std::list<Worm*>::iterator m_AliveWormIterator;

	bool m_suicid;

	bool m_isDead;
};

