#include "stdafx.h"
#include "Level.h"
#include "Map.h"
#include "EventManager.h"
namespace Echo
{
	Level::Level(Map* map, EventManager& manager) :
		//m_Geometry(map->GetGeometry()),
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
		auto geometry = m_CurrentMap->GetGeometry();
        for(auto it = geometry.begin(); it != geometry.end();)
        {
			Object* obj = *it;
            obj->Update(deltaTime);
			it++;
        }
    }
    void Level::Draw()
    {
		auto geometry = m_CurrentMap->GetGeometry();
		for (auto it = geometry.begin(); it != geometry.end();)
		{
			Object* obj = *it;
			obj->Draw();
			it++;
		}
    }
	void Level::DetectCollisions()
	{
		auto geometry = m_CurrentMap->GetGeometry();
		// my physics math could/should probably be put into a physics world class, however to save me some time I will write them here
		for (int x = 0; x < geometry.size(); x++)
		{
			for (int y = 0; y < geometry.size(); y++)
			{
				// prevent the object from colliding with itself
				if (geometry[x] == geometry[y])
					continue;
				Echo::AABB& objAABB = geometry[x]->GetAABB();
				Echo::AABB& otherAABB = geometry[y]->GetAABB();
				// send to both objects who hit it, this could be changed to be a manifold containing all data relating to collisions,
				// ie: normals and the objects involved
				// Determine the smallest overlap
				Vector2 normal;
				float penetrationDepth;
				Vector2& pos = geometry[x]->GetPosition();

				if ((geometry[x]->GetLayerMask() & geometry[y]->GetLayer()) != geometry[y]->GetLayer())
					continue;

				if (!objAABB.Overlaps(otherAABB))
					continue;


				auto result = objAABB.GetCollisionNormal(otherAABB);
				CollisionEvent* collision = new CollisionEvent(geometry[x], geometry[y], result.first, result.second);
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
		//m_Geometry = newMap->GetGeometry();
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