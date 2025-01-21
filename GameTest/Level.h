#pragma once
#include "stdafx.h"
#include "Object.h"
#include "EventListener.h"
namespace Echo
{
	class Map;
	class Level : public EventListener
	{
	public:
		Level(EventManager& manager);
		~Level();
		void Update(float deltaTime);
		void Draw();
		void DetectCollisions();
		void AddToLayout(Object* obj) { m_Layout.push_back(obj); }
		void RemoveFromLayout(Object* obj);
		void AddMap(Map* newMap) { m_Maps.push_back(newMap); }
		void LoadMap(Map* newMap);
		virtual void RecieveEvent(Event* pEvent) override;
		Map* GetMap() const { return m_CurrentMap; }
		std::vector<Object*> GetLayout() const { return m_Layout; }
		void ChangeMap();
	private:
		std::vector<Object*> m_Layout;
		Map* m_CurrentMap;
		EventManager& m_Manager;
		std::vector<Map*> m_Maps;
		
	};
}

