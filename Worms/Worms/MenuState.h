/**
 \file	MenuState.h

 \brief	Declares the menu state class.
 */

#pragma once
#include "gamestate.h"
#include <functional>
#include "Button.h"

/**
 \brief	Menu state.

 \sa	GameState
 */

class MenuState :public GameState
{
public:

	/**
	 \brief	Finalizes an instance of the MenuState class.
	 */

	virtual ~MenuState(void);

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
	 \brief	Gets the instance.
	
	 \return	null if it fails, else the instance.
	 */

	static MenuState* getInstance(void){return &m_MenuState;}

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
	 \brief	Initializes a new instance of the MenuState class.
	 */

	MenuState(void);

	void swichToState(GameState* state){
		m_swichToState = state;
	}

	static MenuState m_MenuState;   ///< State of the menu

	std::vector<Button*> m_Buttons; ///< The buttons
	
	GameState* m_swichToState;
};

/**
// End of MenuState.h
 */

