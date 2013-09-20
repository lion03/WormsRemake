/**
\file	GameEngine.cpp

\brief	Implements the game engine class.
*/

#include "GameEngine.h"
#include "GameState.h"

/**
\brief	Change state.

\param [in,out]	state	If non-null, the state.
*/

void GameEngine::ChangeState(GameState * state){

	if(!m_states.empty()){

		m_states.back()->CleanUp();
		m_states.pop_back();

	}

	m_states.push_back(state);
	m_states.back()->Init(this);


}

/**
\brief	Pushes a state.

\param [in,out]	state	If non-null, the state.
*/

void GameEngine::PushState(GameState* state){

	if(!m_states.empty()){
		m_states.back()->Pause();
	}

	m_states.push_back(state);
	m_states.back()->Init(this);

}

/**
\brief	Clean up.
*/

void GameEngine::CleanUp(void){

	while(!m_states.empty()){

		m_states.back()->CleanUp();
		m_states.pop_back();
	}

}

/**
\brief	Pops the state.
*/

void GameEngine::PopState(){
	if(!m_states.empty()){

		m_states.back()->CleanUp();
		m_states.pop_back();

	}

	if(!m_states.empty())
		m_states.back()->Resume();
}

/**
\brief	Updates this object.
*/

void GameEngine::Update(void){
#ifdef _KINECT
	if(m_KinectActive){
		sensor->NuiSkeletonGetNextFrame(0,&ourframe);
	
		sf::Vector2i mousePos;
		for (int i = 0; i < 6; i++)
		{
			if (ourframe.SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED){
				mousePos = sf::Vector2i(ourframe.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].x,
										ourframe.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].y);

				sf::Mouse::setPosition(mousePos);
			}
		}
	}
#endif
	m_states.back()->Update(this);

}

/**
\brief	Draws this object.
*/

void GameEngine::Draw(void){
	m_Window.clear();

	m_states.back()->Draw(this);
#ifdef _DEBUG
	m_MouseCursorSprite.setPosition( m_Window.mapPixelToCoords(sf::Mouse::getPosition(m_Window)));
	m_Window.draw(m_MouseCursorSprite);
#endif
	m_Window.display();
}

/**
\brief	Quits this object.
*/

void GameEngine::Quit(void){

	m_running = false;
	m_Window.close();
#ifdef _KINECT
	sensor->NuiShutdown();
#endif
}

/**
\brief	Handles the events.
*/

void GameEngine::HandleEvents(void){

	m_states.back()->HandleEvents(this);

}

/**
// End of GameEngine.cpp
*/

