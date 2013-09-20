/**
 \file	SplashState.h

 \brief	Declares the splash state class.
 */

#pragma once
#include <SFML/Audio.hpp>
#include "gamestate.h"
#include <iostream>

using namespace std;

/**
 \brief	Splash state.

 \sa	GameState
 */

class SplashState :public GameState
{
public:

	/**
	 \brief	Finalizes an instance of the SplashState class.
	 */

	virtual ~SplashState(void);

	/**
	 \brief	Initialises this object.
	 */

	void Init(GameEngine* game);

	/**
	 \brief	Clean up.
	 */

	void CleanUp(void);

	/**
	 \brief	Pauses this object.
	 */

	void Pause(void);

	/**
	 \brief	Resumes this object.
	 */

	void Resume(void);

	/**
	 \brief	Handles the events described by game.
	
	 \param [in,out]	game	If non-null, the game.
	 */

	void HandleEvents(GameEngine* game);

	/**
	 \brief	Gets the instence.
	
	 \return	null if it fails, else the instence.
	 */

	static SplashState& getInstence(void) {
		static SplashState m_SpalshState;
		return m_SpalshState;
	}

	/**
	 \brief	Draws the given game.
	
	 \param [in,out]	game	If non-null, the game.
	 */

	void Draw(GameEngine* game);

	/**
	 \brief	Updates the given game.
	
	 \param [in,out]	game	If non-null, the game.
	 */

	void Update(GameEngine* game);
private:

	/**
	 \brief	Initializes a new instance of the SplashState class.
	 */

	SplashState(void);

	sf::Music m_SpalshMusic;	///< The splash music
	sf::Texture m_SplashTexture;	///< The splash texture
	sf::Sprite m_SplashSprite;  ///< The splash sprite
};

/**
// End of SplashState.h
 */

