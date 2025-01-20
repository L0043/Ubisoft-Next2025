#pragma once
#include "stdafx.h"
#include "AABB.h"
#include "App/app.h"
#include "Draw.h"
namespace Echo
{
    AABB::AABB(Vector2 position, float width, float height,Vector4 colour)
    {
        m_Position = position;
        m_Scale = Vector2(width, height);
        m_Min = Vector2(m_Position.x - m_Scale.x / 2, m_Position.y - m_Scale.y / 2);
        m_Max = Vector2(m_Position.x + m_Scale.x / 2, m_Position.y + m_Scale.y / 2);
        m_Colour = colour;
    }
    AABB::~AABB()
    {
    }
    void AABB::Update()
    {

        m_Min.x = m_Position.x - m_Scale.x / 2;
        m_Min.y = m_Position.y - m_Scale.y / 2;

        m_Max.x = m_Position.x + m_Scale.x / 2;
        m_Max.y = m_Position.y + m_Scale.y / 2;
    }

    void AABB::Draw()
    {
        // top right to top left
        ::Draw(m_Max, Vector2(m_Min.x, m_Max.y), m_Colour);
        // top left to bottom left
        ::Draw(Vector2(m_Min.x, m_Max.y), Vector2(m_Min.x , m_Min.y), m_Colour);
        // bottom left to bottom right
        ::Draw(m_Min, Vector2(m_Max.x, m_Min.y), m_Colour);
        // bottom right to top right
        ::Draw(Vector2(m_Max.x, m_Min.y), m_Max, m_Colour);

    }
    void AABB::SetPosition(Vector2 position)
    {
        m_Position = position;
        m_Min = Vector2(m_Position.x - m_Scale.x / 2, m_Position.y - m_Scale.y / 2);
        m_Max = Vector2(m_Position.x + m_Scale.x / 2, m_Position.y + m_Scale.y / 2);
    }
    void AABB::SetScale(Vector2 scale)
    {
        m_Scale = scale;
        m_Min = Vector2(m_Position.x - m_Scale.x / 2, m_Position.y - m_Scale.y / 2);
        m_Max = Vector2(m_Position.x + m_Scale.x / 2, m_Position.y + m_Scale.y / 2);
    }
    std::pair<Vector2, float> AABB::GetCollisionNormal(const AABB& other)
    {
        Vector2 normal;
        float penetrationDepth;

        // Calculate the overlap along the x-axis
        float overlapX1 = m_Max.x - other.GetMin().x;
        float overlapX2 = other.GetMax().x - m_Min.x;
        float overlapX = (std::min)(overlapX1, overlapX2);

        // Calculate the overlap along the y-axis
        float overlapY1 = m_Max.y - other.GetMin().y;
        float overlapY2 = other.GetMax().y - m_Min.y;
        float overlapY = (std::min)(overlapY1, overlapY2);

        // Determine the smallest overlap and set the collision normal
        if (overlapX < overlapY)
        {
            // Move along the x-axis
            if (m_Position.x < other.GetPosition().x)
            {
                normal = Vector2(-1, 0); // Collision on the left side
            }
            else
            {
                normal = Vector2(1, 0); // Collision on the right side
            }
            penetrationDepth = overlapX;
        }
        else
        {
            // Move along the y-axis
            if (m_Position.y < other.GetPosition().y)
            {
                normal = Vector2(0, -1); // Collision on the bottom side
            }
            else
            {
                normal = Vector2(0, 1); // Collision on the top side
            }
            penetrationDepth = overlapY;
        }

        return { normal, penetrationDepth };
    }
    bool AABB::Overlaps(AABB& other)
    {
        // check other's bounds to see if they are within this one's bounds
        // mockUpper is a modified m_TopRight and mockLower is a modified m_BottomLeft
        Vector2 p1 = other.m_Min - m_Max;
        Vector2 p2 = m_Min - other.m_Max;

        if (p1.x > 0.0f || p1.y > 0.0f)
            return false;
        if (p2.x > 0.0f || p2.y > 0.0f)
            return false;

        return true;
    }
}