#include "stdafx.h"
#include "Goal.h"
#include "Ball.h"
namespace Echo
{
    Goal::Goal(MeshType meshType, ObjectType objType, Vector2 position, Vector2 size, Vector4 colour,Level* level, CSimpleSprite sprite):
        Object(position, size, 0, colour, meshType,objType,level, &sprite)
    {
        isDebug = true;
        isStatic = true;
        m_AABB.SetScale({ m_Size.x * 2.0f, m_Size.x * 2.0f });
        m_LayerMask = ~ObjectType::Terrain;
    }

    Goal::~Goal()
    {
    }

    void Goal::Update(float deltaTime)
    {
        Object::Update(deltaTime);
    }

    void Goal::Draw()
    {
        Object::Draw();
        if (text)
            App::Print(400, 400, "Goal Hit!");
    }

    void Goal::OnCollision(CollisionData* data)
    {
        if (isCollisionProcessed)
            return;
        //if(data->m_ObjB->GetType() == ObjectType::GolfBall)
        //{
        //    text = true;
        //    GoalHit();
        //}
        isCollisionProcessed = true;
    }

    void Goal::GoalHit()
    {
    }
}
