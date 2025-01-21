#pragma once
#include "Wall.h"
namespace Echo
{
	// this is the class every wall in the game is made from, I wanted to have some sort of echolocation in the game.
	// If I had kept every wall as 4 lines, the entire thing would be revealed at one time. So I broke them into many pieces all of the Wall class, 
	// that way they could be treated like objects and have easy access to update and draw calls, and have individual collision detection
	// this class could 1000% use some optimization as having too many segments slows the game down heavily.
	class SegmentedWall : public Object
	{
	public:
		SegmentedWall(Vector2 position, Vector2 scale, int numDivisions, Level* level, Map* map, 
			bool isMoving = false, Vector2 min = {}, Vector2 max = {}, bool left = false, float speed = 50);
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