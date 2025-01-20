#pragma once
#include "Events.h"
namespace Echo
{
	class EventListener
	{
	public:
		virtual void RecieveEvent(Event*) = 0;
	};
}