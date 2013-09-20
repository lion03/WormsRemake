/**
 \file	Animation.h

 \brief	Declares the animation class.
 */

#pragma once
#include<map>
#include<SFML/Graphics.hpp>
#include "TinyXML/tinyxml.h"

/**
 \brief	Animation.
 */

class Animation
{
public:

	/**
	 \brief	Initializes a new instance of the Animation class.
	
	 \param [in,out]	animationSetElement	If non-null, the animation set element.
	 */

	Animation(TiXmlElement *animationSetElement)
	{
		assert(animationSetElement->ValueTStr() == "spr");

		TiXmlElement* root = animationSetElement;

		while (root)
		{
			sf::IntRect frame(std::stoi(root->Attribute("x")),std::stoi(root->Attribute("y")),std::stoi(root->Attribute("w")),std::stoi(root->Attribute("h")));
			std::string framrName(root->Attribute("name"));
			m_AninmationSet.insert(std::make_pair(framrName,frame));
			root = root->NextSiblingElement();
		}

		m_CurrFrame = m_AninmationSet.begin();
	}

	virtual ~Animation(void)
	{
	}

	/**
	 \brief	Searches for the first match for the given constant standard string&amp;
	
	 \param	str	The.
	
	 \return	null if it fails, else.
	 */

	sf::IntRect* find(const std::string& str){

		return &m_AninmationSet.find(str)->second;

	}

	/**
	 \brief	Gets the setp play.
	
	 \return	null if it fails, else.
	 */

	sf::IntRect* setpPlay(){
		

		if(m_CurrFrame == m_AninmationSet.end())
			rewind();

		sf::IntRect* temp = &m_CurrFrame->second;

		++m_CurrFrame;

		return temp;
	}

	/**
	 \brief	Rewinds this object.
	 */

	virtual void rewind(){
		m_CurrFrame = m_AninmationSet.begin();
	}
private:

	/**
	 \brief	Defines an alias representing name of the frame.
	 */

	typedef std::string FrameName;

	/**
	 \brief	Defines an alias representing set the animation belongs to.
	 */

	typedef std::map<FrameName,sf::IntRect> AnimationSet;
	typedef AnimationSet::iterator Frame;

	Frame m_CurrFrame;  ///< The curr frame
	AnimationSet m_AninmationSet;   ///< Set the aninmation belongs to



	int frameRate;  ///< The frame rate


};

