/**
 \file	ObjectDetroyer.h

 \brief	Declares the object destroyer class.
 */

#pragma once
#include <set>
#include <list>
#include <vector>
#include <Box2D/Box2D.h>

//#include "GameObject.h"
class GameObject;

/**
 \brief	Object destroyer.
 */

class ObjectDetroyer
{
public:

	/**
	 \brief	Initializes a new instance of the ObjectDetroyer class.
	
	 \param [in,out]	mainObjectList	If non-null, list of main objects.
	 */

	ObjectDetroyer(std::list<GameObject* >* mainObjectList):m_mainObjectList(mainObjectList)
	{
	}

	/**
	 \brief	Finalizes an instance of the ObjectDetroyer class.
	 */

	virtual ~ObjectDetroyer(void)
	{

	}

	void killAll();
	/**
	 \brief	Kill all.
	 */

	

	/**
	 \brief	Adds an object to kill list.
	
	 \param [in,out]	gameObject	If non-null, the game object.
	 */

	virtual void addObjectToKillList(GameObject * gameObject){

		m_killList.push_back(gameObject);

	}



private:

	std::vector<GameObject*> m_killList;   ///< List of kills

	std::list<GameObject* > * m_mainObjectList;   ///< List of main objects

};

