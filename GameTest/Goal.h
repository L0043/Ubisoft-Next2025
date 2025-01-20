#pragma once
#include "Object.h"
namespace Echo
{
	class Goal : public Object
	{
	public:
		Goal(MeshType meshType, ObjectType objType, Vector2 position, Vector2 size, Vector4 colour, Level* level, CSimpleSprite sprite);
		~Goal();
		virtual void Update(float deltaTime) override;
		virtual void Draw() override;
		virtual void OnCollision(CollisionData* data) override;
		void GoalHit();
	private:
		bool text = false;
	};
}