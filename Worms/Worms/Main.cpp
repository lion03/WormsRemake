/**
\file	Main.cpp

\brief	Implements the main class.
*/

#ifdef _DEBUG
#include <vld.h>
#endif
#include <SFML/Graphics.hpp>
#include "GameEngine.h"
#include "SplashState.h"
#include "ResourceManager.h"
#include <SFML/Graphics.hpp>
#include "MapLoader.h"
#include "External/TinyXML/tinystr.h"
#include "External/TinyXML/tinyxml.h"
#include "Macros.h"
#include "PlayState.h"
#include <iostream>
#include <sstream>
using namespace std;
/**
\brief	Main entry-point for this application.

\return	Exit-code for the process - 0 for success, else an error code.
*/

int main(int argc, char** argv){


	GameEngine game;

	srand(std::time(0));		



#ifdef _DEBUG

	ResourceManager<sf::Texture>::getInstence()->registerResource("Resource/Maps/textures/artText.gif","GND");

#else
	ResourceManager<sf::Texture>::getInstence()->registerResource(argv[3],"GND");

#endif
	ResourceManager<sf::Texture>::getInstence()->getResource("GND").get()->setRepeated(true);
	ResourceManager<sf::Texture>::getInstence()->registerResource("Resource/Other/QuitGame.png","QuitGame");
	ResourceManager<sf::Texture>::getInstence()->registerResource("Resource/Other/NewGame.png","NewGame");
	ResourceManager<sf::Texture>::getInstence()->registerResource("Resource/Other/minus.png","minus");
	ResourceManager<sf::Texture>::getInstence()->registerResource("Resource/Other/plus.png","plus");
	ResourceManager<sf::Texture>::getInstence()->registerResource("Resource/Other/uzi.jpg","uzi");
	ResourceManager<sf::Texture>::getInstence()->registerResource("Resource/Other/shotgun.png","shotgun");
	ResourceManager<sf::Texture>::getInstence()->registerResource("Resource/Other/bazooka.jpg","bazooka");
	MapLoader mapLoader(std::string("Resource/Maps/Maps.svg"));
	ResourceManager<sf::SoundBuffer>::getInstence()->registerResource("Resource/Sound/SFX/explosion3.wav","bazookaExp"); 
	ResourceManager<sf::SoundBuffer>::getInstence()->registerResource("Resource/Sound/SFX/rocketrelease.wav","bazookaFire"); 
	ResourceManager<sf::SoundBuffer>::getInstence()->registerResource("Resource/Sound/SFX/shotgunreload.wav","shotGunLoad"); 
	ResourceManager<sf::SoundBuffer>::getInstence()->registerResource("Resource/Sound/SFX/shotgunfire.wav","shotGunFire"); 
	ResourceManager<sf::SoundBuffer>::getInstence()->registerResource("Resource/Sound/SFX/uzifire.wav","uziFire"); 


#ifdef _DEBUG
	PlayState::getInstence().setNumOfPlayers(2);
	PlayState::getInstence().setMap(*ResourceManager<MapLoader::GameMap>::getInstence()->getResource("map1"));
#else
	PlayState::getInstence().setNumOfPlayers(atoi(argv[1]));	
	PlayState::getInstence().setMap(*ResourceManager<MapLoader::GameMap>::getInstence()->getResource(string(argv[2])).get());
#endif
	game.PushState(&PlayState::getInstence());
	while (game.Running())
	{
		if(game.Running())
			game.HandleEvents();
		if(game.Running())
			game.Update();
		game.Draw();

	}




	//delete buff;
	//	delete text;
	return EXIT_SUCCESS;
}

/**
// End of Main.cpp
*/

