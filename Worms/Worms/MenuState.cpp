/**
\file	MenuState.cpp

\brief	Implements the menu state class.
*/

#include "MenuState.h"
#include "SplashState.h"
#include "PlayState.h"
#include "NewGameState.h"
MenuState MenuState::m_MenuState;

/**
 \brief	Initializes a new instance of the MenuState class.
 */

MenuState::MenuState(void):m_swichToState(nullptr)
{
}

/**
 \brief	Finalizes an instance of the MenuState class.
 */

MenuState::~MenuState(void)
{
	CleanUp();
}

/**
 \brief	Initialises this object.

 \param [in,out]	game	If non-null, the game.
 */

void MenuState::Init(GameEngine* game){

	m_Buttons.push_back(new Button(sf::Vector2f(180.f,300.f),sf::Vector2f(864.f,130.f)));
	m_Buttons.back()->addFunction(new ActionFunc0Arg<GameEngine>(std::tr1::mem_fn<void,GameEngine>(&GameEngine::Quit),game));
	*m_Buttons.back()+= "QuitGame";
	m_Buttons.back()->setActive();
	m_Buttons.push_back(new Button(sf::Vector2f(180.f,100.f),sf::Vector2f(864.f,130.f)));
	m_Buttons.back()->addFunction(new ActionFunc1Arg<MenuState, GameState*>(std::tr1::mem_fn(&MenuState::swichToState),this,&NewGameState::getInstence()));
	*m_Buttons.back()+= "NewGame";
	m_Buttons.back()->setActive();
}

/**
 \brief	Clean up.
 */

void MenuState::CleanUp(void){

	
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

void MenuState::Pause(void){}

/**
 \brief	Resumes this object.
 */

void MenuState::Resume(void){}

/**
 \brief	Handles the events described by game.

 \param [in,out]	game	If non-null, the game.
 */

void MenuState::HandleEvents(GameEngine* game){



	sf::Event Event;


	if(game->getWindow()->pollEvent(Event)){
		EventDispatcher::getInstance()->notifyAll(Event);
		switch (Event.type)
		{
		case sf::Event::Closed:
			game->Quit();
			break;
		case sf::Event::KeyPressed:
			switch (Event.key.code)
			{
			case sf::Keyboard::F1:

				break;
			case sf::Keyboard::Escape:
				game->Quit();
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}

	}
}

/**
 \brief	Draws the given game.

 \param [in,out]	game	If non-null, the game.
 */

void MenuState::Draw(GameEngine* game){

	for (auto it = m_Buttons.begin(); it != m_Buttons.end(); it++)
	{
		game->getWindow()->draw(**it);
	}


}

/**
 \brief	Updates the given game.

 \param [in,out]	game	If non-null, the game.
 */

void MenuState::Update(GameEngine* game){
	if(m_swichToState){

		game->ChangeState(m_swichToState);

	}
}

/**
// End of MenuState.cpp
*/

