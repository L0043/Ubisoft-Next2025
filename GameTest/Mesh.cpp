#include "stdafx.h"
#include "Mesh.h"

namespace Echo
{
    Mesh::Mesh(MeshType type, Vector2& position, Vector4& colour,float arg1, float arg2):
        m_Position(position),
        m_Colour(colour)
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
            break;
        }
    }
    // explicit copy constructor
    Mesh::Mesh(const Mesh& other):
        m_Position(other.m_Position),
        m_Colour(other.m_Colour),
        m_Type(other.m_Type),
        m_Arg1(other.m_Arg1),
        m_Arg2(other.m_Arg2),
        m_Vertices(other.m_Vertices)
    {
    
    }
    // explicit assignment operator
    //Mesh& Mesh::operator=(const Mesh& other)
    //{
    //
    //        m_Type = other.m_Type;
    //        m_Position = other.m_Position;
    //        m_Colour = other.m_Colour;
    //        m_Arg1 = other.m_Arg1;
    //        m_Arg2 = other.m_Arg2;
    //        m_Vertices = other.m_Vertices;
    //    
    //    return *this;
    //}
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
    void Mesh::Draw()
    {
        for (int i = 0; i < m_Vertices.size(); i++)
        {
            Vector2 start = m_Vertices[i] + m_Position;
            Vector2 end = m_Vertices[(i + 1) % m_Vertices.size()] + m_Position;
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
            break;
        }
    }
    void Mesh::CreateTriangle(float width, float height)
    {
        m_Vertices.push_back(Vector2(-width / 2, -height / 2));
        m_Vertices.push_back(Vector2(width / 2, -height / 2));
        m_Vertices.push_back(Vector2(0, height / 2));
    }
}