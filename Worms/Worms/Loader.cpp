/**
 \file	Loader.cpp

 \brief	Implements the loader class.
 */

#include "Loader.h"


Loader::Loader(void):m_settingsFile("Animations/WormFly/newSpriteSheet1.xml")
{

	assert(m_settingsFile.LoadFile());

	TiXmlNode* root = m_settingsFile.FirstChildElement();

	if(root){
		if(root->ValueTStr() == "settings"){

			root = root->FirstChildElement();
			
			while (root)
			{
				if(root->ValueTStr() == "Animation")
					AnimationDB::loadAnimations(root->ToElement());

				root = root->NextSiblingElement();
			}
			//std::string path = root->ToElement()->Attribute("name");
			
			//m_AnimationDB.first.loadFromFile("Resource/Animation/"+path);
			
		}
		/*
		for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
		{

			std::string elemName = elem->Value();
			if(elemName == "dir"){
				std::string animationName = elem->Attribute("name");
				TiXmlElement* animationNode = elem->FirstChildElement();
				
				std::map<std::string,sf::IntRect> temp;
				while (animationNode)
				{
					if(animationNode->Value() == std::string("spr")){

						int x = std::stof(animationNode->Attribute("x"));
						int y = std::stof(animationNode->Attribute("y"));
						int w = std::stof(animationNode->Attribute("w"));
						int h = std::stof(animationNode->Attribute("h"));
						std::string frameName = animationNode->Attribute("name");
						temp.insert(std::make_pair(frameName,sf::IntRect(x,y,w,h)));

					}
					animationNode = animationNode->NextSiblingElement();
				}
				m_AnimationDB.second.insert(std::make_pair(animationName,temp));
			}
		}
		*/
	}

}


Loader::~Loader(void)
{
}
