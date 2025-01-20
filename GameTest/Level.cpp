#include "stdafx.h"
#include "Level.h"
#include "Map.h"
#include "EventManager.h"
namespace Echo
{
	Level::Level(Map* map, EventManager& manager) :
		m_Geometry(map->GetGeometry()),
		m_CurrentMap(map),
		m_Manager(manager)
    {
		manager.RegisterListener(this, CollisionEvent::GetStaticEventType());
    }
    Level::~Level()
    {
    }
    void Level::Update(float deltaTime)
    {
        for(Object* obj : m_Geometry)
        {
            obj->Update(deltaTime);
        }
    }
    void Level::Draw()
    {
        for (Object* obj : m_Geometry)
            obj->Draw();
    }
	void Level::DetectCollisions()
	{
		// my physics math could/should probably be put into a physics world class, however to save me some time I will write them here
		for (Echo::Object* obj : m_Geometry)
		{
			for (int i = 0; i < m_Geometry.size(); i++)
			{
				// prevent the object from colliding with itself
				if (m_Geometry[i] == obj)
					continue;
				Echo::AABB& objAABB = obj->GetAABB();
				Echo::AABB& otherAABB = m_Geometry[i]->GetAABB();
				// send to both objects who hit it, this could be changed to be a manifold containing all data relating to collisions,
				// ie: normals and the objects involved
				// Determine the smallest overlap
				Vector2 normal;
				float penetrationDepth;
				Vector2& pos = obj->GetPosition();
				if (!objAABB.Overlaps(otherAABB))
					continue;


				auto result = objAABB.GetCollisionNormal(otherAABB);
				CollisionEvent* collision = new CollisionEvent(obj, m_Geometry[i], result.first, result.second);
				m_Manager.AddEvent(collision);
				//obj->OnCollision(m_Geometry[i], normal);
				//m_Geometry[i]->OnCollision(obj, normal);
				//if (!obj->IsStatic())
				//{
				//	normal = result.first;
				//	penetrationDepth = result.second;
				//	Vector2 pos = obj->GetPosition();
				//	pos += normal * (penetrationDepth * 1.01);
				//	obj->SetPosition(pos + normal * penetrationDepth);
				//
				//}
			}
		}
	}
	void Level::LoadMap(Map* newMap)
	{
		m_Geometry = newMap->GetGeometry();
		m_CurrentMap = newMap;
	}
	void Level::RecieveEvent(Event* pEvent)
	{
		// this is set up for only CollisionEvents, to make it able to be used for multiple types,
		// add brackets to if statement and remove return
		if (pEvent->GetType() != CollisionEvent::GetStaticEventType())
			return;
		CollisionEvent* ColEvent = static_cast<CollisionEvent*>(pEvent);
		ColEvent->GetObjA()->OnCollision(&ColEvent->GetData());
		ColEvent->GetObjB()->OnCollision(&ColEvent->GetData());
	}
}