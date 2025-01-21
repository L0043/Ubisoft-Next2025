#include "stdafx.h"
#include "Wall.h"
#include "Level.h"
#include "Map.h"
namespace Echo
{
    Wall::Wall(Vector2 position, Vector2 scale, float rotation, Level* m_Level, MeshType meshType, ObjectType objType) :
        Object(position, scale, rotation, {0, 0, 0, 1}, meshType, objType, m_Level)
    {
        m_LayerMask = ~ObjectType::Terrain & ~ObjectType::Interactible;
        isStatic = true;
        m_Name = "Wall";
        m_Colour = { 0,0,0,1 };
        m_AABB.SetColor({ 0,0,0,1 });
    }

    Wall::~Wall()
    {
    }

    void Wall::Update(float deltaTime)
    {
        if (!isActive)
            return;
        Object::Update(deltaTime);

        m_Colour -= 1.0f * deltaTime;
        
        if (m_Colour <= Vector4{0,0,0,0})
        {
            isCollisionProcessed = false;
            isActive = false;
        }
    }

    void Wall::Draw()
    {
        if(isActive)
            Object::Draw();
    }
    void Wall::OnCollision(CollisionData* data)
    {
        if (isCollisionProcessed)
            return;
        // if collide with soundwave, activate visuals
        isActive = true;
        m_Colour = { 1, 1, 1, 1 };
        isCollisionProcessed = true;
    }
}