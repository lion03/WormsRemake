#include "NewGameState.h"


NewGameState::NewGameState(void):m_NumberOfPlayers(2), m_SwichToState(nullptr)
{
}


NewGameState::~NewGameState(void)
{

	CleanUp();

}

/**
\brief	Initialises this object.

\param [in,out]	game	If non-null, the game.
*/

void NewGameState::Init(GameEngine*game)
{
	m_Buttons.push_back(new Button(sf::Vector2f(200.f,100.f),sf::Vector2f(30,199.f)));
	m_Buttons.back()->addFunction(new ActionFunc0Arg<NewGameState>(std::tr1::mem_fn(&NewGameState::removePlayer),this));
	m_Buttons.back()->setActive();
	*m_Buttons.back()+= "minus";
	m_Buttons.push_back(new Button(sf::Vector2f(400.f,100.f),sf::Vector2f(30,199.f)));
	m_Buttons.back()->addFunction(new ActionFunc0Arg<NewGameState>(std::tr1::mem_fn(&NewGameState::addPlayer),this));
	*m_Buttons.back()+= "plus";
	m_Buttons.back()->setActive();
	m_Buttons.push_back(new Button(sf::Vector2f(300.f,500.f),sf::Vector2f(50,50)));
	m_Buttons.back()->addFunction(new ActionFunc0Arg<NewGameState>(std::tr1::mem_fn(&NewGameState::setPlayState),this));

	m_Buttons.back()->setActive();


	font.loadFromFile("ariblk.ttf");
	m_NumberOfPlayersText.setFont(font);
	m_NumberOfPlayersText.setPosition(300.f,150.f);

}

/**
\brief	Updates the given game.

\param [in,out]	game	If non-null, the game.
*/

void NewGameState::Update(GameEngine*game)
{
	std::stringstream ss;

	ss << m_NumberOfPlayers;

	m_NumberOfPlayersText.setString(ss.str());

	if(m_SwichToState)
		game->ChangeState(m_SwichToState);
}

/**
\brief	Draws the given game.

\param [in,out]	game	If non-null, the game.
*/

void NewGameState::Draw(GameEngine*game)
{
	game->getWindow()->draw(m_NumberOfPlayersText);

	for (auto it = m_Buttons.begin(); it != m_Buttons.end(); it++)
	{
		game->getWindow()->draw(**it);
	}

}

/**
\brief	Handles the events described by game.

\param [in,out]	game	If non-null, the game.
*/

void NewGameState::HandleEvents(GameEngine*game)
{
	sf::Event Event;
	if(game->getWindow()->pollEvent(Event))
		EventDispatcher::getInstance()->notifyAll(Event);
}

/**
\brief	Clean up.
*/

void NewGameState::CleanUp(void)
{
	for(auto it = m_Buttons.begin() ; it != m_Buttons.end();){
		delete *it;
		it = m_Buttons.erase(it);
		if(it == m_Buttons.end())
			break;
	}

	m_Buttons.clear();
}

/**
\brief	Pauses this object.
*/

void NewGameState::Pause(void)
{

}

/**
\brief	Resumes this object.
*/

void NewGameState::Resume(void){

}

