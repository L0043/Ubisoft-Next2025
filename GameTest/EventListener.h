#pragma once
#include "Events.h"
namespace Echo
{
	// an abstract class designed soley to allow other classes to inherit from it and receive events from the manager
	
	class EventListener
	{
	public:
		virtual void RecieveEvent(Event*) = 0;
	};
}