/**
 \file	Arsenal.h

 \brief	Declares the arsenal class.
 */

#pragma once
#include <list>
#include <map>
#include "GuiObject.h"
#include "Button.h"
#include "Bazooka.h"
#include "Shotgun.h"
#include "Uzi.h"
#define MAP_INSERT(a,b) std::make_pair(a,b)


class WeaponProperty;
class Team;

/**
 \brief	Arsenal.

 \sa	GuiObject
 */

class Arsenal : public GuiObject
{
public:

	friend class Team;
	/**
	 \brief	Defines an alias representing name of the weapon.
	 */

	typedef std::string WeaponName;

	/**
	 \brief	Initializes a new instance of the Arsenal class.
	 */

	Arsenal(void);

	/**
	 \brief	Initializes a new instance of the Arsenal class.
	
	 \param	cellSize			Size of the cell.
	 \param [in,out]	team	If non-null, the team.
	 */

	Arsenal(const sf::Vector2f &cellSize,Team* team);

	/**
	 \brief	Finalizes an instance of the Arsenal class.
	 */

	virtual ~Arsenal(void);

	/**
	 \brief	Receive event.
	
	 \param	Event	The event.
	 */

	virtual void receiveEvent(const sf::Event &Event);

	/**
	 \brief	Inserts a weapon.
	
	 \param	name			   	The name.
	 \param [in,out]	propert	If non-null, the propert.
	 */

	//virtual void insertWeapon(const WeaponName &name, WeaponProperty * propert){m_TheArsenal.insert(MAP_INSERT(name,propert));}

	void setActive(bool active);

protected:

	/**
	 \brief	Draws.
	
	 \param [in,out]	target	Target for the.
	 \param	states			  	The states.
	 */

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const ;

private:

	std::vector<Weapon*> m_TheArsenal;  ///< the arsenal

	sf::RectangleShape m_Bounds;	///< The bounds

	sf::Vector2f m_CellSize;	///< Size of the cell

	int m_rowIndex; ///< Zero-based index of the row

	int m_colIndex; ///< Zero-based index of the col

	std::vector<sf::RectangleShape*> m_Buttons; ///< The buttons

	std::list<Button*> m_Button;	///< The button

	Team* m_Team;   ///< The team

};

/**
// End of Arsenal.h
 */

