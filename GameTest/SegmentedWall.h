#pragma once
#include "Wall.h"
namespace Echo
{
	class SegmentedWall : public Object
	{
	public:
		SegmentedWall(Vector2 position, Vector2 scale, int numDivisions, Level* level, Map* map, bool isMoving = false, Vector2 min = {}, Vector2 max = {}, bool left = false, float speed = 50);
		~SegmentedWall();
		virtual void Update(float deltaTime) override;
	private:
		const int m_NumOfDivisionsPerSide;
		std::vector<Wall*> m_Segments;
		std::vector<Vector2> m_SegmentOffsets;
		Map* m_Map;
		bool isMoving = false;
		bool isMovingLeft = false;
		Vector2 m_MinPos;
		Vector2 m_MaxPos;
		float m_Speed;

	};
}