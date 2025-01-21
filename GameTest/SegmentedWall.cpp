#include "stdafx.h"
#include "SegmentedWall.h"
#include "Map.h"
namespace Echo
{
    SegmentedWall::SegmentedWall(Vector2 position, Vector2 size, int numDivisions, Level* level, Map* map, bool isMoving, Vector2 min, Vector2 max, bool left, float speed):
        Object(position, size, 0, {0,0,0,1}, MeshType::Rect, ObjectType::Terrain, level),
        m_NumOfDivisionsPerSide(numDivisions/4),
        m_Map(map)
    {
        m_LayerMask = ~ObjectType::Terrain;
        isStatic = true;
        float minX = m_AABB.GetMin().x;
        float minY = m_AABB.GetMin().y;
        float maxX = m_AABB.GetMax().x;
        float maxY = m_AABB.GetMax().y;

        float segmentWidth = (maxX - minX) / m_NumOfDivisionsPerSide;
        float segmentHeight = (maxY - minY) / m_NumOfDivisionsPerSide;

         

        // Create bottom and top walls
        for (int i = 0; i < m_NumOfDivisionsPerSide; i++) {
            float posX = minX + i * segmentWidth + segmentWidth / 2;

            // Bottom wall segment
            Wall* wallBottom = new Wall({ posX, minY }, { segmentWidth, 1 }, 0, m_Level, MeshType::Rect, ObjectType::Terrain);
            wallBottom->SetColour(m_Colour);
            wallBottom->GetAABB().SetColor(m_Colour);
            wallBottom->m_Name = "Segment";
            m_Segments.push_back(wallBottom);
            m_SegmentOffsets.push_back(Vector2(posX, minY) - m_Position);

            // Top wall segment
            Wall* wallTop = new Wall({ posX, maxY }, { segmentWidth, 1 }, 0, m_Level, MeshType::Rect, ObjectType::Terrain);
            wallTop->SetColour(m_Colour);
            wallTop->GetAABB().SetColor(m_Colour);
            wallTop->m_Name = "Segment";
            m_Segments.push_back(wallTop);
            m_SegmentOffsets.push_back(Vector2(posX, maxY) - m_Position);
        }

        // Create left and right walls
        for (int i = 0; i < m_NumOfDivisionsPerSide; i++) {
            float posY = minY + i * segmentHeight + segmentHeight / 2;

            // Left wall segment
            Wall* wallLeft = new Wall({ minX, posY }, { 1, segmentHeight }, 0, m_Level, MeshType::Rect, ObjectType::Terrain);
            wallLeft->SetColour(m_Colour);
            wallLeft->GetAABB().SetColor(m_Colour);
            wallLeft->m_Name = "Segment";
            m_Segments.push_back(wallLeft);
            m_SegmentOffsets.push_back(Vector2(minX, posY) - m_Position);

            // Right wall segment
            Wall* wallRight = new Wall({ maxX, posY }, { 1, segmentHeight }, 0, m_Level, MeshType::Rect, ObjectType::Terrain);
            wallRight->SetColour(m_Colour);
            wallRight->GetAABB().SetColor(m_Colour);
            wallRight->m_Name = "Segment";
            m_Segments.push_back(wallRight);
            m_SegmentOffsets.push_back(Vector2(maxX, posY )- m_Position);
        }

        for(int i = 0; i < m_Segments.size(); i++)
        {
            m_Map->AddGeometry(m_Segments[i]);
        }

        // for moving walls
        this->isMoving = isMoving;
        m_MinPos = min;
        m_MaxPos = max;
        m_Speed = speed;
        isMovingLeft = left;

    }

    SegmentedWall::~SegmentedWall()
    {
    }

    void SegmentedWall::Update(float deltaTime)
    {
        Object::Update(deltaTime);
        if (!isMoving)
            return;
        Vector2 pos = m_Position;
        if(isMovingLeft)
        {
            pos += Vector2(-1, 0) * deltaTime * m_Speed;
            if (pos.x <= m_MinPos.x)
                isMovingLeft = !isMovingLeft;
        }
        if(!isMovingLeft)
        {
            pos += Vector2(1, 0) * deltaTime * m_Speed;
            if (pos.x >= m_MaxPos.x)
                isMovingLeft = !isMovingLeft;
        }

        m_Position = pos;

        for(int i = 0; i < m_Segments.size(); i++)
        {
            Vector2 initialOffset = m_SegmentOffsets[i];
            Vector2 newPosition = m_Position + initialOffset;
            m_Segments[i]->SetPosition(newPosition);
            m_Segments[i]->Update(deltaTime);
        }
    }

}
