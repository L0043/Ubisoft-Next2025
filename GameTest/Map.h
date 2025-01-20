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
		void AddGeometry(Object* object) { m_Geometry.push_back(object); }
		void CreateGeometry(MeshType meshType, ObjectType objType, Vector2 position, Vector2 args, Vector4 colour, float rotation);
		std::vector<Object*> GetGeometry() { return m_Geometry; }
	private:
		std::vector<Object*> m_Geometry;
		Level* m_pLevel;
	};
}