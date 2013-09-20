/**
 \file	SplashState.cpp

 \brief	Implements the splash state class.
 */

#include "SplashState.h"
#include "MenuState.h"

/**
 \brief	Initializes a new instance of the SplashState class.
 */

SplashState::SplashState(void)
{

	

}

/**
 \brief	Finalizes an instance of the SplashState class.
 */

SplashState::~SplashState(void)
{
}

/**
 \brief	Initialises this object.

 \param [in,out]	game	If non-null, the game.
 */

void SplashState::Init(GameEngine* game)
{

	m_SpalshMusic.openFromFile("Resource/Sound/WWP_Title.ogg");
	m_SpalshMusic.setLoop(true);
	m_SpalshMusic.play();
	m_SplashTexture.loadFromFile("Resource/BackGrounds/Splash.png");
	m_SplashSprite.setTexture(m_SplashTexture);

}

/**
 \brief	Clean up.
 */

void SplashState::CleanUp(void)
{

	m_SpalshMusic.stop();

}

/**
 \brief	Pauses this object.
 */

void SplashState::Pause(void)
{



}

/**
 \brief	Resumes this object.
 */

void SplashState::Resume(void)
{
}

/**
 \brief	Handles the events described by game.

 \param [in,out]	game	If non-null, the game.
 */

void SplashState::HandleEvents(GameEngine* game)
{

	sf::Event Event;

	if(game->getWindow()->pollEvent(Event)){

		switch (Event.type)
		{
		case sf::Event::Closed:
			game->Quit();
			break;
		case sf::Event::KeyPressed:
			if(Event.key.code == sf::Keyboard::Escape){
				game->Quit();
			}
		case sf::Event::MouseButtonPressed:

			game->ChangeState(MenuState::getInstance());

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

void SplashState::Draw(GameEngine* game){

	game->getWindow()->draw(m_SplashSprite);

}

/**
 \brief	Updates the given game.

 \param [in,out]	game	If non-null, the game.
 */

void SplashState::Update(GameEngine* game){}

/**
// End of SplashState.cpp
 */

