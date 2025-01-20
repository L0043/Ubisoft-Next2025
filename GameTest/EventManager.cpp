#pragma once
#include "stdafx.h"
#include "EventManager.h"
#include "EventListener.h"
#include "Events.h"
namespace Echo
{
	EventManager::EventManager()
	{
	}
	EventManager::~EventManager()
	{
		while (!m_Queue.empty())
			m_Queue.pop();
	}
	void EventManager::AddEvent(Event* pEvent)
	{
		m_Queue.push(pEvent);
	}
	void EventManager::ProcessQueue()
    {
		while (!m_Queue.empty())
		{
			Event* pEvent = m_Queue.front();
			m_Queue.pop();

			if (!m_Listeners[pEvent->GetType()].empty())
			{

				for (int i = 0; i < m_Listeners[pEvent->GetType()].size(); i++)
				{
					m_Listeners[pEvent->GetType()][i]->RecieveEvent(pEvent);
				}
			}
			delete pEvent;
		}
    }
}