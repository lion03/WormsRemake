/**
\file	EventDispatcher.h

\brief	Declares the event dispatcher class.
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <functional>
#include <algorithm>
//#include "EventListener.h"


class EventListener;

/**
\brief	Event dispatcher.
*/


class EventDispatcher
{
public:



	virtual ~EventDispatcher(void)
	{
	}

	void registerListener(EventListener* listener){m_listeners.push_back(listener);}

	void notifyAll(const sf::Event &Event);

	void removeListener(EventListener* listener){
		for(auto it = m_listeners.begin() ; it != m_listeners.end() ; ++it){
			if(*it == listener){
				m_LitenerIterator = m_listeners.erase(it);
				return;
			}
		}
		//m_listeners.remove(listener);
		
	}

	static EventDispatcher* getInstance(void){return &m_dispatcher;} 

private:

	static EventDispatcher m_dispatcher;

	
	EventDispatcher(void)
	{
	}

	std::list<EventListener*> m_listeners;

	std::list<EventListener*>::iterator m_LitenerIterator;

};


/**
\brief	Event listener.
*/

class EventListener
{
public:

	/**
	 \brief	Initializes a new instance of the EventListener class.
	 */

	EventListener(void)
	{
		EventDispatcher::getInstance()->registerListener(this);
	}

	/**
	 \brief	Finalizes an instance of the EventListener class.
	 */

	virtual ~EventListener(void)
	{
		EventDispatcher::getInstance()->removeListener(this);
	}

	/**
	\brief	Receive event.

	\param	Event	The event.
	*/

	virtual void receiveEvent(const sf::Event& Event) = 0;
};

/**
// End of EventDispatcher.h
 */

