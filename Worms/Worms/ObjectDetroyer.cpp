/**
 \file	ObjectDetroyer.cpp

 \brief	Implements the object detroyer class.
 */

#include "ObjectDetroyer.h"
#include "GameObject.h"
#include "Projectile.h"
#include "Worm.h"
#include "Ground.h"

/**
 \brief	Kill all.
 */

void ObjectDetroyer::killAll(){

	for (unsigned int it = 0 ; it < m_killList.size(); it++)
	{
		

		//b2Body* body = dyingGameObject->getBody();


		auto x = m_killList[it];
		

		
		auto it1 = std::find(m_mainObjectList->begin(),m_mainObjectList->end(), m_killList[it]);

		if(it1 != m_mainObjectList->end()){

			delete (*it1);
			//m_mainObjectList->erase(it1);
		}
	

	}

	m_killList.clear();
	//m_mainObjectList->shrink_to_fit();
}