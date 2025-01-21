#include "stdafx.h"
#include "Mesh.h"

namespace Echo
{
    Mesh::Mesh(MeshType type, Vector2& position, Vector4& colour, float& rotation,float arg1, float arg2):
        m_Position(position),
        m_Colour(colour),
        m_Rotation(rotation)
    {
        m_Type = type;
        m_Arg1 = arg1;
        m_Arg2 = arg2;
        switch (m_Type)
        {
        case MeshType::Rect:
            CreateRect(arg1, arg2);
            break;
        case MeshType::Circle:
            CreateCircle(arg1, arg2);
            break;
        case MeshType::Triangle:
            CreateTriangle(arg1, arg2);
        case MeshType::Arrow:
            CreateArrow(arg1, arg2);
            break;
        }
    }
    // explicit copy constructor
    Mesh::Mesh(const Mesh& other):
        m_Position(other.m_Position),
        m_Colour(other.m_Colour),
        m_Rotation(other.m_Rotation),
        m_Type(other.m_Type),
        m_Arg1(other.m_Arg1),
        m_Arg2(other.m_Arg2),
        m_Vertices(other.m_Vertices)
    {
    
    }
    Mesh::~Mesh()
    {
    }
    void Mesh::CreateRect(float width, float height)
    {
        m_Vertices.push_back(Vector2(-width / 2, -height / 2));
        m_Vertices.push_back(Vector2(width / 2, -height / 2));
        m_Vertices.push_back(Vector2(width / 2, height / 2));
        m_Vertices.push_back(Vector2(-width / 2, height / 2));
    }
    void Mesh::CreateCircle(float radius, int segments)
    {
        for (int i = 0; i < segments; i++)
        {
            float angle = 2 * PI * i / segments;
            m_Vertices.push_back(Vector2(cos(angle) * radius, sin(angle) * radius));
        }
    }

    Vector2 RotateVertex(const Vector2& vert, float angle)
    {
        float radians = angle * (PI / 180.0f);
        float cosAngle = cosf(radians);
        float sinAngle = sinf(radians);

        float x = vert.x * cosAngle - vert.y * sinAngle;
        float y = vert.x * sinAngle + vert.y * cosAngle;
        return Vector2(x, y);
    }

    void Mesh::Draw()
    {
        for (int i = 0; i < m_Vertices.size(); i++)
        {
            // Rotate the current vertex
            Vector2 startVert = RotateVertex(m_Vertices[i], m_Rotation);
            Vector2 start = startVert + m_Position;

            // Rotate the next vertex
            Vector2 endVert = RotateVertex(m_Vertices[(i + 1) % m_Vertices.size()], m_Rotation);
            Vector2 end = endVert + m_Position;

            // Draw the line between the rotated vertices
            ::Draw(start, end, m_Colour);
        }
    }
    void Mesh::UpdateMesh(float arg1, float arg2)
    {
        m_Vertices.clear();
        switch (m_Type)
        {
        case MeshType::Rect:
            CreateRect(arg1, arg2);
            break;
        case MeshType::Circle:
            CreateCircle(arg1, arg2);
            break;
        case MeshType::Triangle:
            CreateTriangle(arg1, arg2);
        case MeshType::Arrow:
            CreateArrow(arg1, arg2);
            break;
        }
    }
    void Mesh::CreateTriangle(float width, float height)
    {
        m_Vertices.push_back(Vector2(-width / 2, -height / 2));
        m_Vertices.push_back(Vector2(width / 2, -height / 2));
        m_Vertices.push_back(Vector2(0, height / 2));
    }
    void Mesh::CreateArrow(float shaftLength, float shaftWidth)
    {

        // Define the shaft (rectangle)
        float halfWidth = shaftWidth / 2;
        m_Vertices.push_back(Vector2(-shaftLength / 2, -halfWidth));
        m_Vertices.push_back(Vector2(shaftLength / 2, -halfWidth));
        m_Vertices.push_back(Vector2(shaftLength / 2, halfWidth));
        m_Vertices.push_back(Vector2(-shaftLength / 2, halfWidth));

        // Define the head (triangle)
        float headLength = shaftLength / 2;
        m_Vertices.push_back(Vector2(shaftLength / 2, -shaftWidth));
        m_Vertices.push_back(Vector2(shaftLength / 2 + headLength, 0));
        m_Vertices.push_back(Vector2(shaftLength / 2, shaftWidth));
    }
}