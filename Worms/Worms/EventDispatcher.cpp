/**
 \file	EventDispatcher.cpp

 \brief	Implements the event dispatcher class.
 */

#include "EventDispatcher.h"

EventDispatcher EventDispatcher::m_dispatcher;

/**
 \brief	Notifies all.

 \param	Event	The event.
 */

void EventDispatcher::notifyAll(const sf::Event &Event){

	//auto receiveFunc = std::tr1::mem_fn(&EventListener::receiveEvent);

	m_LitenerIterator = m_listeners.begin();

	while (m_LitenerIterator != m_listeners.end())
	{
		(**m_LitenerIterator).receiveEvent(Event);

		++m_LitenerIterator;
	}

	/*
	for(auto it = m_listeners.begin() ; it != m_listeners.end() ; ++it){
		(**it).receiveEvent(Event);
	}
	*/
}

/**
// End of EventDispatcher.cpp
 */

