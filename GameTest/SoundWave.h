#pragma once
#include "Object.h"
namespace Echo 
{
	// this class will instantiate from the collision point and spread for its duration, it will then destroy itself
	// all Walls that it collides with will be revealed
	class SoundWave : public Object
	{
	public:
		SoundWave(Vector2 position, float radius, float segments, const char* filename, 
			float duration, Level* m_Level, MeshType meshType = MeshType::Circle, ObjectType objType = ObjectType::Metaphysical);
		~SoundWave();
		virtual void Update(float deltaTime) override;
		virtual void Draw() override;
		virtual void OnCollision(CollisionData* data) override;

	private:
		const float m_Duration = 10; //duration in seconds
		float m_Timer = 0;
		const char* m_fileName;
		float m_Radius;
		float m_Speed = 100;
	};
}