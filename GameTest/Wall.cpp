#include "stdafx.h"
#include "Wall.h"

namespace Echo
{
    Wall::Wall(Vector2 position, Vector2 scale, float rotation, Level* m_Level, MeshType meshType, ObjectType objType) :
        Object(position, scale, rotation, {0, 0, 0, 1}, meshType, objType, m_Level)
    {
        m_LayerMask = ~ObjectType::Terrain;
        isStatic = true;
        m_Name = "Wall";
        //isDebug = true;
        m_Colour = { 0,0,0,1 };
        m_AABB.SetColor({ 1,0,0,1 });
    }

    Wall::~Wall()
    {
    }

    void Wall::Update(float deltaTime)
    {
        Object::Update(deltaTime);

        if(isActive)
        {
            m_Colour -= 1.0f * deltaTime;
        }
    }

    void Wall::Draw()
    {
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