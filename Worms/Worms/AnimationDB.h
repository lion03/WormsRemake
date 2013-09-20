/**
 \file	AnimationDB.h

 \brief	Declares the animation database class.
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "TinyXML/tinyxml.h"
#include "DataBase.h"
//#include "Animation.h"

/**
 \brief	Animation database.

 \sa	DataBase
 */

class AnimationDB : public DataBase
{
public:

	typedef std::string FrameName;
	typedef std::string SetName;
	typedef std::map<FrameName,sf::IntRect> AnimationSet;
	typedef std::pair<sf::Texture,std::map<SetName,Animation>> AnimationsMap;

private:
	std::string m_dbFileName;
public:

	AnimationDB(void){}

	virtual ~AnimationDB(void)
	{
	}

	static void loadAnimations(TiXmlElement* animationElement){

		assert(animationElement->ValueTStr() == "Animation");

		std::string path = animationElement->Attribute("path");

		assert(m_animationMap.first.loadFromFile("Resource/Animation/"+path));

		TiXmlElement* animationSet = animationElement->FirstChildElement();

		while (animationSet)
		{
			//m_animationMap.second.insert(std::make_pair(animationSet->Attribute("name"),Animation(animationSet->FirstChildElement())));
			animationSet= animationSet->NextSiblingElement();
		}


	}

	static AnimationsMap* getAnimationDB() {return &m_animationMap;}

	//static Animation* find(const std::string & str){return &m_animationMap.second.find(str)->second;}
private:

	static AnimationsMap m_animationMap;
};

