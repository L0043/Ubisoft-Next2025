#pragma once
#include "Object.h"
namespace Echo
{
	// The map is essentially a scene, it holds all static geometry and it drawn upon when needed by the level
	// for instance, inserting the geometry into the level's layout so they can be rendered and updated in time with all other objects
	class Level;
	class Map
	{
	public:
		Map();
		~Map();
		void AttachLevel(Level* level) { m_pLevel = level; }
		void AddGeometry(Object* object);
		void RemoveGeometry(Object* object);
		//void CreateGeometry(MeshType meshType, ObjectType objType, Vector2 position, Vector2 args, Vector4 colour, float rotation);
		std::vector<Object*> GetGeometry() { return m_Geometry; }
		void SetStartingPosition(Vector2 pos) { m_StartingPosition = pos; }
		void SetGoalStartingPosition(Vector2 pos) { m_GoalStartingPosition = pos; }
		Vector2 GetStartingPosition() const { return m_StartingPosition; }
		Vector2 GetGoalStartingPosition() const { return m_GoalStartingPosition; }
	private:
		std::vector<Object*> m_Geometry;
		Level* m_pLevel;
		Vector2 m_StartingPosition;
		Vector2 m_GoalStartingPosition;
	};
}