#include "stdafx.h"
#include "SegmentedWall.h"
namespace Echo
{
    SegmentedWall::SegmentedWall(Vector2 position, Vector2 scale, int numDivisions, Level* level):
        Object(position, scale, 0, {1,1,1,1}, MeshType::Rect, ObjectType::Terrain, level),
        m_NumOfDivisionsPerSide(numDivisions)
    {
        isStatic = true;
        float offsetY = m_Size.y / (float)m_NumOfDivisionsPerSide;
        for(int i = 1; i < m_NumOfDivisionsPerSide; i++)
        {
            Wall* wall = new Wall({ m_AABB.GetMax().x, m_AABB.GetMax().y - (offsetY * i)}, {3,3}, 0, m_Level, MeshType::Rect, ObjectType::Terrain);
            wall->SetColour({ 0,1,0,1 });
            wall->GetAABB().SetColor({ 0,1,0,1 });
            wall->m_Name = "Segment";
            m_Segments.push_back(*wall);
        }
    }

    SegmentedWall::~SegmentedWall()
    {
    }
}
