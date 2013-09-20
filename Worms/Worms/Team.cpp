/**
\file	Team.cpp

\brief	Implements the team class.
*/

#include "Team.h"
#include "Weapon.h"
#include "Arsenal.h"

/**
\brief	Initializes a new instance of the Team class.

\param [in,out]	world			 	If non-null, the world.
\param [in,out]	objectDetroyer   	If non-null, the object detroyer.
\param [in,out]	mainGameObjectVec	If non-null, the main game object vector.
\param	teamSize					 	Size of the team.
\param	teamColor					 	The team color.
*/

Team::Team(b2World* world, ObjectDetroyer* objectDetroyer, std::list<GameObject*>* mainGameObjectVec, uint8 teamSize, const sf::Color& teamColor):
	m_PtrToObjDestroyer(objectDetroyer),
	m_PtrToMainGameObjVec(mainGameObjectVec),
	m_TeamSize(teamSize),
	m_TeamColor(teamColor),
	m_WeaponName(""),
	m_Active(false),
	m_isDead(false),
	m_suicid(false)
{


	m_TeamArsenal = new Arsenal(sf::Vector2f(50.f,50.f),this);

	for (int i = 0; i < teamSize; i++)
	{
		m_TeamMembers.push_back(new Worm(world,objectDetroyer,mainGameObjectVec,this,m_TeamColor,sf::Vector2f(rand()%2560,0)));
		m_AliveWorms.push_back(m_TeamMembers.back());
		m_TeamMembers.back()->setActive(false);
		mainGameObjectVec->push_back(m_TeamMembers.back());
	}
	//m_WormIterator = m_TeamMembers.begin();
	m_AliveWormIterator = m_AliveWorms.begin();
	index = 0;
}

/**
\brief	Finalizes an instance of the Team class.
*/

Team::~Team(void)
{
	for (unsigned int i = 0; i < m_TeamMembers.size(); i++)
	{
		delete m_TeamMembers[i];
	}

	m_TeamMembers.clear();

	delete m_TeamArsenal;
}

/**
\brief	Receive event.

\param	Event	The event.
*/

void Team::receiveEvent(const sf::Event&Event)
{

	if(m_Active){
		std::string name = "";
		switch (Event.type)
		{
		case sf::Event::KeyPressed:
			switch (Event.key.code)
			{
			case sf::Keyboard::Tab:

				//m_TeamMembers[index]->setActive(false);
				(*m_AliveWormIterator)->setActive(false);
				++m_AliveWormIterator;
				//++index;

				if(m_AliveWormIterator == m_AliveWorms.end())
					m_AliveWormIterator = m_AliveWorms.begin();

				if(!m_AliveWorms.empty()){
					(*m_AliveWormIterator)->setActive();
				}
				/*
				if(index >= m_TeamMembers.size())
				index = 0;

				m_TeamMembers[index]->setActive();
				*/
				break;
			default:
				break;
			}

			break;
		case sf::Event::MouseButtonPressed:
			break;
		default:
			break;
		}
		if(!m_AliveWorms.empty()){
			m_ActiveWorm = *m_AliveWormIterator;

		}
		else
		{
			m_ActiveWorm = nullptr;
		}

		//m_ActiveWorm = m_TeamMembers[index];
	}
}

/**
\brief	Draws.

\param [in,out]	target	Target for the.
\param	states			  	The states.
*/

void Team::draw(sf::RenderTarget&target, sf::RenderStates states) const
{

	int teamHealth = 0;
	sf::Text totalHealth;
	for (auto it = m_TeamMembers.begin(); it != m_TeamMembers.end(); it++)
	{
		teamHealth += (**it).getHealth();
		//target.draw(**it);
	}

	target.draw(*m_TeamArsenal);

	totalHealth.setString(std::to_string((long long)teamHealth));
}

/**
\brief	Sets an active.

\param	active	true to active.
*/

void Team::setActive(bool active)
{
	m_Active = active;

	/*
	for (auto it = 0 ; i < m_TeamArsenal->m_Button.size(); i++)
	{
	m_TeamArsenal->m_Button.at(i)->setActive(m_Active);
	}
	*/


	if(!m_Active){
		for (unsigned int i = 0; i < m_TeamMembers.size(); i++)

			m_TeamMembers[i]->setActive(false);

		index = 0;
	}
	else{
		(*m_AliveWorms.begin())->setActive();
		m_AliveWormIterator = m_AliveWorms.begin();
		//m_TeamMembers[index]->setActive();

	}



	m_TeamArsenal->setActive(active);

}

/**
\brief	Gets the active.

\return	true if it succeeds, false if it fails.
*/

bool Team::getActive(void) const
{

	return m_Active;
}

/**
\brief	Gets team health.

\return	The team health.
*/

unsigned int Team::getTeamHealth(void)
{

	int teamHealth = 0;
	for (auto it = m_TeamMembers.begin(); it != m_TeamMembers.end(); it++)
	{

		if((**it).getHealth() <= 0)
			m_AliveWorms.remove(*it);

		teamHealth += (**it).getHealth();
		//target.draw(**it);
	}
	if(teamHealth <= 0){
		m_isDead = true;
		return 0;	
	}
	return teamHealth;
}

