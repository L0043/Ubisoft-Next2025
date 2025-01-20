#pragma once
#include "Object.h"
namespace Echo
{
	// used so event type names can be written easily
	using EventType = const char*;

	class Event
	{
		friend class EventManager;
	public:
		Event() {};
		virtual ~Event() = 0 {};
		virtual EventType GetType() = 0;
	};

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