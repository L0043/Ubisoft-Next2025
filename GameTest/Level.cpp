#include "stdafx.h"
#include "Level.h"
#include "Map.h"
#include "EventManager.h"
namespace Echo
{
	Level::Level(EventManager& manager) :
		//m_Geometry(map->GetGeometry()),
		m_CurrentMap(nullptr),
		m_Manager(manager)
    {
		manager.RegisterListener(this, CollisionEvent::GetStaticEventType());
    }
    Level::~Level()
    {
		while (!m_Layout.empty())
			m_Layout.pop_back();
		while (!m_Maps.empty())
			m_Maps.pop_back();
    }
    void Level::Update(float deltaTime)
    {

		//auto geometry = m_CurrentMap->GetGeometry();
        for(Object* object : m_Layout)
        {
			if(object)
				object->Update(deltaTime);
        }
    }
    void Level::Draw()
    {

		//auto geometry = m_CurrentMap->GetGeometry();
		for (Object* object : m_Layout)
		{
			if (object)
				object->Draw();
		}
    }
	void Level::DetectCollisions()
	{
		//auto geometry = m_CurrentMap->GetGeometry();
		// my physics math could/should probably be put into a physics world class, however to save me some time I will write them here
		for (int x = 0; x < m_Layout.size(); x++)
		{
			for (int y = 0; y < m_Layout.size(); y++)
			{
				// prevent the object from colliding with itself
				if (m_Layout[x] == m_Layout[y])
					continue;
				Echo::AABB& objAABB = m_Layout[x]->GetAABB();
				Echo::AABB& otherAABB = m_Layout[y]->GetAABB();
				// send to both objects who hit it, this could be changed to be a manifold containing all data relating to collisions,
				// ie: normals and the objects involved
				// Determine the smallest overlap
				Vector2 normal;
				float penetrationDepth;
				Vector2& pos = m_Layout[x]->GetPosition();

				if ((m_Layout[x]->GetLayerMask() & m_Layout[y]->GetLayer()) != m_Layout[y]->GetLayer())
					continue;

				if (!objAABB.Overlaps(otherAABB))
					continue;


				auto result = objAABB.GetCollisionNormal(otherAABB);
				CollisionEvent* collision = new CollisionEvent(m_Layout[x], m_Layout[y], result.first, result.second);
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
	void Level::RemoveFromLayout(Object* object)
	{
		const auto removed = std::remove(m_Layout.begin(), m_Layout.end(), object);
		if (removed != m_Layout.end())
			m_Layout.erase(removed);
	}
	// I personally feel as though there are most likely a miriade of better solutions to my problem of 
	// accessing the map geometry at the same time as the non static objects, unfortunately this is the best I could come up with.
	void Level::LoadMap(Map* newMap)
	{
		//m_Geometry = newMap->GetGeometry();

		//remove old geometry if map exists
		if (m_CurrentMap)
		{
			for (Object* obj : m_CurrentMap->GetGeometry())
			{
				const auto removed = std::remove(m_Layout.begin(), m_Layout.end(), obj);
				if (removed != m_Layout.end())
					m_Layout.erase(removed);
			}
		}
		m_CurrentMap = newMap;

		// add new geometry
		for (Object* obj : m_CurrentMap->GetGeometry())
		{
			m_Layout.push_back(obj);
		}
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
	void Level::ChangeMap()
	{
		int random = rand() % m_Maps.size();
		switch (random)
		{
		case 0:
			LoadMap(m_Maps[0]);
			break;
		case 1:
			LoadMap(m_Maps[1]);
			break;
		case 2:
			LoadMap(m_Maps[2]);
			break;
		default:
			LoadMap(m_Maps[0]);
			break;
		}
	}
}