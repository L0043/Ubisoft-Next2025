#pragma once
#include "Wall.h"
namespace Echo
{
	class SegmentedWall : Object
	{
	public:
		SegmentedWall(Vector2 position, Vector2 scale, int numDivisions, Level* level);
		~SegmentedWall();
		
	private:
		const int m_NumOfDivisionsPerSide;
		std::vector<Wall> m_Segments;
	};
}