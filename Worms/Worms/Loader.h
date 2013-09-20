/**
 \file	Loader.h

 \brief	Declares the loader class.
 */

#pragma once
#include "TinyXML/tinyxml.h"
//#include "AnimationDB.h"
#include <SFML/Graphics.hpp>

/**
 \brief	Loader.
 */

class Loader
{
public:
	typedef std::string FrameName;
	typedef std::string SetName;
	typedef std::map<FrameName,sf::IntRect> AnimationSet;
	//typedef std::pair<sf::Texture,std::map<SetName,AnimationSet>> AnimationDB;
	Loader(void);
	virtual ~Loader(void);


	sf::Texture m_SpriteSheet;
	//AnimationDB m_AnimationDB;

private:

	//AnimationDB m_animationDB;
	TiXmlDocument m_settingsFile;
	

};

