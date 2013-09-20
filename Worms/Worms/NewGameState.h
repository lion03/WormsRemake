#pragma once
#include "gamestate.h"
#include "MapLoader.h"
#include "PlayState.h"
#include <functional>
#include "Button.h"
#include <sstream>
class NewGameState :
	public GameState
{
public:

	/**
	\brief	Initialises this object.

	\param [in,out]	game	If non-null, the game.
	*/

	void Init(GameEngine* game);

	/**
	\brief	Updates the given game.

	\param [in,out]	game	If non-null, the game.
	*/

	void Update(GameEngine* game);

	/**
	\brief	Draws the given game.

	\param [in,out]	game	If non-null, the game.
	*/

	void Draw(GameEngine* game);

	/**
	\brief	Handles the events described by game.

	\param [in,out]	game	If non-null, the game.
	*/

	void HandleEvents(GameEngine* game);

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
	\brief	Gets the instence.

	\return	The instence.
	*/

	static NewGameState& getInstence(void){
		static NewGameState m_PlayState;
		return m_PlayState;
	}

	virtual ~NewGameState(void);

private:

	NewGameState(void);

	unsigned int m_NumberOfPlayers;

	void addPlayer(void){
		++m_NumberOfPlayers;
		if(m_NumberOfPlayers > 4)
			m_NumberOfPlayers = 2;
	}

	void removePlayer(void){
		--m_NumberOfPlayers;
		if(m_NumberOfPlayers <2)
			m_NumberOfPlayers = 4;
	}

	void setPlayState(void) {
		PlayState::getInstence().setNumOfPlayers(m_NumberOfPlayers);
		unsigned int numOfMaps = rand() % ResourceManager<MapLoader::GameMap>::getInstence()->getResourceMap()->size();

		PlayState::getInstence().setMap(*ResourceManager<MapLoader::GameMap>::getInstence()->getResourceMap()->begin()->second.get());

		m_SwichToState = &PlayState::getInstence();
	}

	std::vector<Button*> m_Buttons; ///< The buttons

	sf::Text m_NumberOfPlayersText;

	sf::Font font;

	GameState* m_SwichToState;
};

