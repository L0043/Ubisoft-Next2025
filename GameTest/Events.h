#pragma once
#include "Object.h"
namespace Echo
{
	// used so event type names can be written easily
	using EventType = const char*;

	class Event
	{
		// this was done so the event manager could access private variables of the class
		// while keeping others from doing the same (i think? im not entirely confident), 
		// though I did directly send the CollisionEvent's data variable to the listeners, whoops.
		friend class EventManager;
	public:
		Event() {};
		virtual ~Event() = 0 {};
		virtual EventType GetType() = 0;
	};
	// I thought it would be good to store all the data in a struct, 
	// keep the info together and make my code a little easier on the eyes
	struct CollisionData
	{
		Object* m_ObjA;
		Object* m_ObjB;
		Vector2 m_Normal;
		float m_PenetrationDepth;
	};

	class CollisionEvent : public Event
	{
	public:
		CollisionEvent(Object* objA, Object* objB, Vector2 normal, float penetrationDepth) :
			m_Data({ objA, objB, normal, penetrationDepth })
		{
		}
		virtual ~CollisionEvent() {};

		static const char* GetStaticEventType() { return "CollisionEvent"; }
		virtual const char* GetType() override { return GetStaticEventType(); }

		Object* GetObjA() const { return m_Data.m_ObjA; };
		Object* GetObjB() const { return m_Data.m_ObjB; };
		const Vector2 GetNormal() const { return m_Data.m_Normal; };
		const float GetPenetrationDepth() const { return m_Data.m_PenetrationDepth; };
		CollisionData GetData() const { return m_Data; }
	private:
		CollisionData m_Data;
	};
}