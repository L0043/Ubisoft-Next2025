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
		Level(Map* map, EventManager& manager);
		~Level();
		void Update(float deltaTime);
		void Draw();
		void DetectCollisions();
		void LoadMap(Map* newMap);
		virtual void RecieveEvent(Event* pEvent) override;
		Map* GetMap() const { return m_CurrentMap; }
	private:
		std::vector<Object*>& m_Geometry;
		Map* m_CurrentMap;
		EventManager& m_Manager;
	};
}

