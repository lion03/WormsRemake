/**
 \file	GameState.h

 \brief	Declares the game state class.
 */

#pragma once
#include "GameEngine.h"
#include <SFML/Graphics.hpp>

/**
 \brief	Game state.
 */

class GameState
{
public:

	/**
	 \brief	Finalizes an instance of the GameState class.
	 */

	~GameState(void);


	
protected:

	/**
	 \brief	Initializes a new instance of the GameState class.
	 */

	GameState(void);

public:

	/**
	 \brief	Initialises this object.
	 */

	virtual void Init(GameEngine* game) = 0;

	/**
	 \brief	Clean up.
	 */

	virtual void CleanUp(void) = 0;

	/**
	 \brief	Pauses this object.
	 */

	virtual void Pause(void) = 0;

	/**
	 \brief	Resumes this object.
	 */

	virtual void Resume(void) = 0;

	/**
	 \brief	Change state.
	
	 \param [in,out]	game 	If non-null, the game.
	 \param [in,out]	state	If non-null, the state.
	 */

	void ChangeState(GameEngine* game, GameState* state)
	{
		game->ChangeState(state);
	}

	/**
	 \brief	Handles the events described by game.
	
	 \param [in,out]	game	If non-null, the game.
	 */

	virtual void HandleEvents(GameEngine* game) = 0;

	/**
	 \brief	Updates the given game.
	
	 \param [in,out]	game	If non-null, the game.
	 */

	virtual void Update(GameEngine* game) = 0;

	/**
	 \brief	Draws the given game.
	
	 \param [in,out]	game	If non-null, the game.
	 */

	virtual void Draw(GameEngine* game) = 0;
};

/**
// End of GameState.h
 */

