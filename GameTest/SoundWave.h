#pragma once
#include "Object.h"
namespace Echo 
{
	// this class will instantiate from the collision point and spread for its duration, it will then destroy itself
	// all Walls/Wall Segments that it collides with will be revealed
	class SoundWave : public Object
	{
	public:
		SoundWave(Vector2 position, float radius, float segments, const char* filename, 
			float duration, Level* m_Level, MeshType meshType = MeshType::Circle, ObjectType objType = ObjectType::Metaphysical);
		~SoundWave();
		virtual void Update(float deltaTime) override;
		virtual void Draw() override;
		virtual void OnCollision(CollisionData* data) override;
		void Destroy();
	private:
		const float m_InitDuration;
		float m_Duration = 2; //duration in seconds
		float m_ColourStep;
		const char* m_FileName;
		float m_Radius;
		float m_Speed = 100;
	};
}