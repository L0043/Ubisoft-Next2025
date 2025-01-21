#pragma once
#include "stdafx.h"
#include "Object.h"
#include "AABB.h"
#include "App/app.h"
#include "Level.h"
#include "Map.h"
namespace Echo
{
    Object::Object(Vector2 position, Vector2 size, float rotation,Vector4 colour, MeshType meshType, ObjectType objType, Level* level):
        m_AABB(position, size.x, size.y, Vector4(1, 1, 1, 1)),
        m_Rotation(rotation),
        m_Mesh(meshType, m_Position, m_Colour, m_Rotation, size.x, size.y),
        m_Position(position),
        m_Size(size),

        m_Colour(colour),
        m_Layer(objType),
        m_Level(level)
    {
        m_LayerMask = ObjectType::GolfBall | ObjectType::Interactible | ObjectType::Terrain| ObjectType::Metaphysical;
        m_InitColour = m_Colour;
    }
    Object::~Object()
    {
        
    }
    void Object::Update(float deltaTime)
    {
        isCollisionProcessed = false;
        m_AABB.SetPosition(m_Position);
        m_AABB.SetColor(m_Colour);
        //if(m_Sprite)
        //{
        //    m_Sprite->SetPosition(m_Position.x, m_Position.y);
        //    m_Sprite->SetScale(m_Size.x);
        //}
    }
    void Object::Draw()
    {
        m_Mesh.Draw();

        if(isDebug)
            m_AABB.Draw();

        //if(m_Sprite)
        //    m_Sprite->Draw();
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