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
	class EventManager
	{
	public:
		EventManager();
		~EventManager();
		void AddEvent(Event* pEvent);
		void ProcessQueue();
		// I would use this if I was making a more generalised engine and wasnt sending the data directly to the parties involved
		// Though I might set it up for the Level class if I have time
		void RegisterListener(EventListener* listener, EventType type)
		{
			m_Listeners[type].push_back(listener);
		}
	private:
		std::queue<Event*> m_Queue;
		std::map<EventType, std::vector<EventListener*>> m_Listeners;
	};
}   