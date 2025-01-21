#pragma once
#include "Object.h"
namespace Echo
{
	// this class is simply the goal post of the minigolf course, 
	class Goal : public Object
	{
	public:
		Goal(MeshType meshType, ObjectType objType, Vector2 position, Vector2 size, Vector4 colour, Level* level);
		~Goal();
		virtual void Update(float deltaTime) override;
		virtual void OnCollision(CollisionData* data) override;
		void SetStartingPosition(Vector2 position) { m_StartingPosition = position; };
		void GoalHit();
		void Reset();
		int GetScore() const { return m_Score; };
	private:
		int m_Score = 0;
		Vector2 m_StartingPosition;
	};
}