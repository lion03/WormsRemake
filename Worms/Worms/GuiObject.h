/**
 \file	GuiObject.h

 \brief	Declares the graphical user interface object class.
 */

#pragma once
#include "ActionFunc.h"
#include "EventDispatcher.h"
#include <vector>


/**
\brief	Graphical user interface object.

\sa	EventDriven
\sa	Listener
\sa	sf::Drawable
*/

class GuiObject : public EventListener ,  public sf::Drawable
{
public:

	/**
	\brief	Initializes a new instance of the GuiObject class.

	\param	pos	The position.
	*/

	GuiObject(const sf::Vector2f &pos){};

	/**
	\brief	Initializes a new instance of the GuiObject class.
	*/

	GuiObject(){};

	/**
	\brief	Finalizes an instance of the GuiObject class.
	*/

	virtual ~GuiObject(void){};

protected:

	/**
	\brief	Draws.

	\param [in,out]	target	Target for the.
	\param	states			  	The states.
	*/

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;

private:

	sf::Vector2f m_Pos; ///< The position

};
