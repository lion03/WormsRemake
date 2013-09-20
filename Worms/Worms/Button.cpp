/**
 \file	Button.cpp

 \brief	Implements the button class.
 */

#include "Button.h"
#include "ResourceManager.h"
/**
 \brief	Finalizes an instance of the Button class.
 */

Button::~Button(void)
{
	for(auto it = m_Actions.begin(); it != m_Actions.end() ;++it){
		
		delete *it;
		it = m_Actions.erase(it);

		if(it == m_Actions.end())
			break;
		
	}
	//EventDispatcher::getInstance()->removeListener(this);
}

/**
 \brief	Highlights.

 \param	highlight	true to highlight.
 */

void Button::highlight(bool highlight){

	m_HighLighted = highlight;

	if (m_HighLighted)
	{
		//m_ButtonShape.setOutlineThickness(m_ButtonShape.getSize().x/10.f);
	}
	else
	{
		//m_ButtonShape.setOutlineThickness(0.f);
	}

}

/**
 \brief	Addition assignment operator.

 \param	picAdrr	The picture adrr.
 */

void Button::operator +=(const std::string &picAdrr){

	m_ButtonShape.setTexture(ResourceManager<sf::Texture>::getInstence()->getResource(picAdrr).get());
	/*
	m_ButtonShape.setSize(sf::Vector2f((float)m_ButtonTexture.getSize().x,(float)m_ButtonTexture.getSize().y));

	m_ButtonShape.setTexture(&m_ButtonTexture);
	*/

}

/**
 \brief	Notifies the given event.

 \param	Event	The event.
 */

void Button::receiveEvent(const sf::Event &Event)
{

	if(Event.type == sf::Event::MouseButtonReleased)
		for(auto it = m_Actions.begin(); it != m_Actions.end() ;++it){	
			if(m_Active && Event.mouseButton.button == sf::Mouse::Left && m_ButtonShape.getGlobalBounds().contains((float)Event.mouseButton.x,(float)Event.mouseButton.y)){
				(*it)->Action();
				return;
			}
		}

}

/**
// End of Button.cpp
 */

