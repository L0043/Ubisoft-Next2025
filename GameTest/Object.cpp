#pragma once
#include "stdafx.h"
#include "Object.h"
#include "AABB.h"
#include "App/app.h"
#include "Level.h"
#include "Map.h"
namespace Echo
{
    Object::Object(Vector2 position, Vector2 size, float rotation,Vector4 colour, MeshType meshType, ObjectType objType, Level* level, CSimpleSprite* sprite):
        m_AABB(position, size.x, size.y, Vector4(1, 1, 1, 1)),
        m_Mesh(meshType, m_Position, m_Colour, size.x, size.y),
        m_Position(position),
        m_Size(size),
        m_Sprite(sprite),
        m_Colour(colour),
        m_Type(objType),
        m_Level(level)
    {
        m_Level->GetMap()->AddGeometry(this);
        auto map = m_Level->GetMap();
        int aj = 5;
    }
    Object::~Object()
    {
        delete m_Sprite;
    }
    void Object::Update(float deltaTime)
    {
        isCollisionProcessed = false;
        m_AABB.SetPosition(m_Position);
        m_AABB.SetColor(m_Colour);
        if(m_Sprite)
        {
            m_Sprite->SetPosition(m_Position.x, m_Position.y);
            m_Sprite->SetScale(m_Size.x);
        }
    }
    void Object::Draw()
    {
        m_Mesh.Draw();

        if(isDebug)
            m_AABB.Draw();

        if(m_Sprite)
            m_Sprite->Draw();
    }
    void Object::OnCollision(CollisionData* data)
    {
        if (isCollisionProcessed || isStatic)
            return;
        // do stuff

        // Calculate the push-back vector
        Vector2 pushBack = (data->m_Normal) * (data->m_PenetrationDepth);
        // Adjust the position of the object
        m_Position += pushBack ;

        // Update the AABB position if necessary
        m_AABB.SetPosition(m_Position);
        isCollisionProcessed = true;
    }

}