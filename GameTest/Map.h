#pragma once
#include "Object.h"
namespace Echo
{
	class Level;
	class Map
	{
	public:
		Map();
		~Map();
		void AttachLevel(Level* level) { m_pLevel = level; }
		void AddGeometry(Object* object);
		void RemoveGeometry(Object* object);
		void CreateGeometry(MeshType meshType, ObjectType objType, Vector2 position, Vector2 args, Vector4 colour, float rotation);
		std::vector<Object*> GetGeometry() { return m_Geometry; }
		void SetStartingPosition(Object* obj, Vector2 pos) { obj->SetPosition(pos); m_StartingPosition = pos; }
	private:
		std::vector<Object*> m_Geometry;
		Level* m_pLevel;
		Vector2 m_StartingPosition;
	};
}