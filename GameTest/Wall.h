#pragma once
#include "stdafx.h"
#include "Object.h"
#include <vector>
namespace Echo
{
    // The walls are going to be the obstacles in the game, they will have an AABB, and be rendered with the drawline func
    // each line will be divided into pieces so that they can be rendered individually.
    // this will allow me to have some portions visible and others not. - not doing this.
	class Wall : public Object
	{
	public:
		Wall(Vector2 position, Vector2 scale, float rotation, Level* m_Level, MeshType type = MeshType::Rect, ObjectType objType = ObjectType::terrain);
		~Wall();
        virtual void Update(float deltaTime) override;
        virtual void Draw() override;
		virtual void OnCollision(CollisionData* data) override;
	private:
		// 
        std::vector<Vector2> m_wallPoints;
		bool isActive;
	};
}