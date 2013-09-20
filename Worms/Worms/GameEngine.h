/**
\file	GameEngine.h

\brief	Declares the game engine class.
*/

#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "StandardCursor.h"
#ifdef _KINECT
#include <NuiApi.h>
#include <NuiImageCamera.h>
#include <NuiSensor.h>
#endif
class GameState;

/**
\brief	Game engine.
*/

class GameEngine
{
public:

	/**
	\brief	Initializes a new instance of the GameEngine class.
	*/

	GameEngine(void):Cursor(StandardCursor::PIC ,"Cursor.cur") {
		
#ifdef _KINECT				// Get a working kinect sensor
		int numSensors;

		if (NuiGetSensorCount(&numSensors) < 0 || numSensors < 1 || NuiCreateSensorByIndex(0, &sensor) < 0) 
			m_KinectActive = false;
		else
		{
			m_KinectActive = true;
		}


		if(m_KinectActive){

			//initKinect();

		}
#endif
#ifndef _DEBUG
		m_Window.create(sf::VideoMode::getDesktopMode(),"Worms",sf::Style::Fullscreen);
		//m_Window.create(sf::VideoMode::getDesktopMode(),"Worms");

#else
		m_Window.create(sf::VideoMode::getDesktopMode(),"Worms");
#endif

		m_Window.setVerticalSyncEnabled(true);
#ifndef _DEBUG

		m_Window.setMouseCursorVisible(false);
		Cursor.set(m_Window.getSystemHandle());
#endif
	}

	/**
	\brief	Finalizes an instance of the GameEngine class.
	*/

	virtual ~GameEngine(void){

		CleanUp();

	};

	/**
	\brief	Clean up.
	*/

	void CleanUp(void);

	/**
	\brief	Change state.

	\param [in,out]	state	If non-null, the state.
	*/

	void ChangeState(GameState * state);

	/**
	\brief	Pushes a state.

	\param [in,out]	state	If non-null, the state.
	*/

	void PushState(GameState* state);

	/**
	\brief	Handles the events.
	*/

	void HandleEvents(void);

	/**
	\brief	Pops the state.
	*/

	void PopState(void);

	/**
	\brief	Updates this object.
	*/

	void Update(void);

	/**
	\brief	Draws this object.
	*/

	void Draw(void);

	/**
	\brief	Runnings this object.

	\return	true if it succeeds, false if it fails.
	*/

	bool Running(void){return m_running;}

	/**
	\brief	Quits this object.
	*/

	void Quit(void);

	/**
	\brief	Gets the window.

	\return	null if it fails, else the window.
	*/

	sf::RenderWindow* getWindow(void) {return &m_Window;}

private:

	bool m_running; ///< true to running

	std::vector<GameState*> m_states;   ///< The states

	sf::RenderWindow m_Window;  ///< The window

	sf::Sprite m_MouseCursorSprite; ///< The mouse cursor sprite

	sf::Texture m_MouseTexture; ///< The mouse texture

	StandardCursor Cursor;  ///< The cursor
#ifdef _KINECT
	// Kinect variables
	HANDLE rgbStream;              // The identifier of the Kinect's RGB Camera
	HANDLE skeletonStream;
	INuiSensor* sensor;            // The kinect sensor

	bool m_KinectActive;

	NUI_SKELETON_FRAME ourframe;

	virtual void initKinect(){
		sensor->NuiInitialize(NUI_INITIALIZE_FLAG_USES_DEPTH | NUI_INITIALIZE_FLAG_USES_COLOR | NUI_INITIALIZE_FLAG_USES_SKELETON);
		sensor->NuiSkeletonTrackingEnable(&skeletonStream,NUI_SKELETON_TRACKING_FLAG_ENABLE_SEATED_SUPPORT);
		sensor->NuiImageStreamOpen(
			NUI_IMAGE_TYPE_COLOR,            // Depth camera or rgb camera?
			NUI_IMAGE_RESOLUTION_640x480,    // Image resolution
			0,      // Image stream flags, e.g. near mode
			2,      // Number of frames to buffer
			NULL,   // Event handle
			&rgbStream);



	}

	sf::Vector2f getKinectScale(const Vector4 & skeletonPoint){

		LONG x,y;
		USHORT depth;

		NuiTransformSkeletonToDepthImage(skeletonPoint,&x,&y,&depth,NUI_IMAGE_RESOLUTION_640x480);

		float screenPointX = static_cast<float>(x*m_Window.getSize().x)/640;
		float screenPointY = static_cast<float>(y*m_Window.getSize().y)/480;

		return sf::Vector2f(screenPointX,screenPointY);
	}
#endif
};

/**
// End of GameEngine.h
*/

