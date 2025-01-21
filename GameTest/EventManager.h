#pragma once
#include <queue>
#include "Object.h"
namespace Echo
{
	// used so event type names can be written easily
	using EventType = const char*;
	class Event;
	class EventListener;
	// try to make this a singleton if you have time
	// I made the event manager solely for the purpose of seperating collision detection from the handling
	// I did my best to make it polymorphic so it could take in all sorts of events and send them to whoever is waiting for them
	class EventManager
	{
	public:
		EventManager();
		~EventManager();
		void AddEvent(Event* pEvent);
		void ProcessQueue();
		// take in the class and what type of event it is looking out for
		void RegisterListener(EventListener* listener, EventType type)
		{
			m_Listeners[type].push_back(listener);
		}
	private:
		std::queue<Event*> m_Queue;
		std::map<EventType, std::vector<EventListener*>> m_Listeners;
	};
}   