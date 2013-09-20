/**
 \file	Button.h

 \brief	Declares the button class.
 */

#pragma once
#include "guiobject.h"
#include <SFML/Graphics.hpp>
#include <list>

/**
 \brief	Button.

 \sa	GuiObject
 */

class Button : virtual public GuiObject
{
public:

	/**
	 \brief	Initializes a new instance of the Button class.
	
	 \param	pos 	The position.
	 \param	size	The size.
	 */

	Button(const sf::Vector2f & pos, const sf::Vector2f &size):m_ButtonShape(size),m_Active(false) {

		m_ButtonShape.setPosition(pos);
		//addClickEvent(std::mem_fn<void,Button>(&Button::highlight),this);
		m_ButtonShape.setFillColor(sf::Color::White);
		m_ButtonShape.setOutlineColor(sf::Color::Yellow);
		highlight(false);
	}

	/**
	 \brief	Adds an external effect function to 'target'.
	
	 \tparam	P	Type of the p.
	 \param	func			  	The function.
	 \param [in,out]	target	If non-null, target for the.
	 */

	template<class P>
	void addExternalEffectFunc(const std::mem_fun_t<void,P> & func, P *target){
		addClickEvent(func,target);
	}

	/**
	 \brief	Finalizes an instance of the Button class.
	 */

	virtual ~Button(void);

	/**
	 \brief	Highlights.
	
	 \param	highlight	true to highlight.
	 */

	virtual void highlight(bool highlight);

	virtual void Hover(void){
	}

	/**
	 \brief	Sets fill color.
	
	 \param	color	The color.
	 */

	virtual void setFillColor(const sf::Color &color){m_ButtonShape.setFillColor(color);}

	/**
	 \brief	Addition assignment operator.
	
	 \param	picAdrr	The picture adrr.
	 */

	virtual void operator+=(const std::string & picAdrr);

	/**
	 \brief	Notifies the given event.
	
	 \param	Event	The event.
	 */

	virtual void receiveEvent(const sf::Event &Event);	
	
	virtual void setActive(bool active = true){m_Active = active;}

	virtual void addFunction(ActionFunc* action){
		m_Actions.push_back(action);
	}

protected:

	/**
	 \brief	Draws.
	
	 \param [in,out]	target	Target for the.
	 \param	states			  	The states.
	 */

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {target.draw(m_ButtonShape);	}


private:

	sf::FloatRect m_ClickableArea;  ///< The clickable area

	bool m_HighLighted; ///< true if high lighted

	sf::Texture m_ButtonTexture;	///< The button texture

	sf::RectangleShape m_ButtonShape;   ///< The button shape

	std::list<ActionFunc*> m_Actions;

	bool m_Active;
};

