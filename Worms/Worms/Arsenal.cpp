/**
\file	Arsenal.cpp

\brief	Implements the arsenal class.
*/

#include "Arsenal.h"
#include "Team.h"

/**
 \brief	Initializes a new instance of the Arsenal class.
 */

Arsenal::Arsenal(void)
{
}

/**
 \brief	Finalizes an instance of the Arsenal class.
 */

Arsenal::~Arsenal(void)
{

	for(auto it = m_Button.begin() ; it != m_Button.end();){
		delete *it;
		it = m_Button.erase(it);
		if(it == m_Button.end())
			break;
	}

	m_Button.clear();

	for(auto it = m_TheArsenal.begin() ; it != m_TheArsenal.end();++it){
		delete *it;
		
		if(it == m_TheArsenal.end())
			break;
	}

	m_TheArsenal.clear();

}

/**
 \brief	Draws.

 \param [in,out]	target	Target for the.
 \param	states			  	The states.
 */

void Arsenal::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	//target.draw(m_Bounds);
	for (auto it = m_Button.begin(); it != m_Button.end(); it++)
	{
		target.draw((**it));
	}
}

/**
 \brief	Receive event.

 \param	Event	The event.
 */

void Arsenal::receiveEvent(const sf::Event &Event)
{

	switch (Event.type)
	{
	case sf::Event::MouseMoved:
		if(m_Bounds.getGlobalBounds().contains(Event.mouseMove.x,Event.mouseMove.y)){
			for (auto it = m_Buttons.begin(); it != m_Buttons.end(); it++)
			{
				if((**it).getGlobalBounds().contains(Event.mouseMove.x,Event.mouseMove.y)){
					(**it).setOutlineThickness(5.f);
				}
				else{
					(**it).setOutlineThickness(0.f);
				}
			}
		}
		else{
			for (auto it = m_Buttons.begin(); it != m_Buttons.end(); it++)
			{

				(**it).setOutlineThickness(0.f);

			}
		}
		break;
	case sf::Event::MouseButtonReleased:

	default:
		break;
	}

}

/**
 \brief	Initializes a new instance of the Arsenal class.

 \param	cellSize			Size of the cell.
 \param [in,out]	team	If non-null, the team.
 */

Arsenal::Arsenal(const sf::Vector2f &cellSize,Team* team):
	m_CellSize(cellSize),
	m_Bounds(sf::Vector2f(cellSize.x * 4,cellSize.y *5)),
	m_rowIndex(0),
	m_colIndex(0),
	m_Team(team)
{

	m_Bounds.setPosition(1000.f,400.f);

	std::tr1::mem_fn(&Team::setWeapon);
	m_TheArsenal.push_back(new Bazooka());
	m_Button.push_back(new Button(sf::Vector2f(0*cellSize.x + m_Bounds.getPosition().x+5,0*cellSize.y),sf::Vector2f(cellSize.x - 5,cellSize.y - 5 )));

	m_Button.back()->addFunction(new ActionFunc1Arg<Team,Weapon*>(std::tr1::mem_fn(&Team::setWeapon),team,m_TheArsenal.back()));
	*m_Button.back()+= "bazooka";
	m_TheArsenal.push_back(new Shotgun());
	m_Button.push_back(new Button(sf::Vector2f(0*cellSize.x + m_Bounds.getPosition().x+5,1*cellSize.y),sf::Vector2f(cellSize.x - 5,cellSize.y - 5 )));
	m_Button.back()->addFunction(new ActionFunc1Arg<Team, Weapon*>(std::tr1::mem_fn(&Team::setWeapon),team,m_TheArsenal.back()));
	*m_Button.back()+= "shotgun";
	m_TheArsenal.push_back(new Uzi());
	m_Button.push_back(new Button(sf::Vector2f(0*cellSize.x + m_Bounds.getPosition().x+5,2*cellSize.y),sf::Vector2f(cellSize.x - 5,cellSize.y - 5 )));
	m_Button.back()->addFunction(new ActionFunc1Arg<Team, Weapon*>(std::tr1::mem_fn(&Team::setWeapon),team,m_TheArsenal.back()));
	*m_Button.back()+= "uzi";

	m_Team->setWeapon(m_TheArsenal.front());
	/*
	for (int i = 0; i < 5; i++)
	{
	for (int j = 0; j < 4; j++)
	{

	m_Buttons.push_back(new sf::RectangleShape(sf::Vector2f(cellSize.x - 5,cellSize.y - 5 )));
	m_Buttons.back()->setPosition(j*cellSize.x + m_Bounds.getPosition().x+5,i*cellSize.y + m_Bounds.getPosition().y+5);
	m_Buttons.back()->setOutlineColor(sf::Color::Yellow);
	}
	}
	*/
}

/**
 \brief	Sets an active.

 \param	active	true to active.
 */

void Arsenal::setActive(bool active)
{
	for(auto it = m_Button.begin() ; it != m_Button.end() ; ++it){
		(*it)->setActive(active);
	}

	if(active){
		m_Team->setWeapon(m_TheArsenal.front());
	}
}

