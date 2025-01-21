#include "stdafx.h"
#include "Goal.h"
#include "Ball.h"
#include "Level.h"
#include "Map.h"
namespace Echo
{
    Goal::Goal(MeshType meshType, ObjectType objType, Vector2 position, Vector2 size, Vector4 colour,Level* level, CSimpleSprite sprite):
        Object(position, size, 0, colour, meshType,objType,level, &sprite)
    {
        isStatic = true;
        m_AABB.SetScale({ m_Size.x * 2.0f, m_Size.x * 2.0f });
        m_LayerMask = ObjectType::GolfBall;
    }

    Goal::~Goal()
    {
    }

    void Goal::Update(float deltaTime)
    {
        Object::Update(deltaTime);
        isCollisionProcessed = false;
    }

    void Goal::OnCollision(CollisionData* data)
    {
        if (isCollisionProcessed)
            return;
        if(data->m_ObjA->GetLayer() == ObjectType::GolfBall)
        {
            Ball* b = dynamic_cast<Ball*>(data->m_ObjA);
            if (b)
                b->Reset();
            GoalHit();
        }
        isCollisionProcessed = true;
    }

    void Goal::GoalHit()
    {
        App::PlaySoundW(".\\TestData\\score.wav");
        m_Level->ChangeMap();
        m_Score++;
    }
}
