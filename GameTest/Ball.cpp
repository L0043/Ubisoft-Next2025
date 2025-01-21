#include "stdafx.h"
#include "Ball.h"
#include "SoundWave.h"
#include "Level.h"
#include "Map.h"
namespace Echo
{
    Ball::Ball(Vector2 position, float radius, int segments, Level* m_Level, MeshType meshType, ObjectType objType) :
        Object(position, {radius, (float)segments}, 0.0f, { 1,1,1,1 }, meshType, objType, m_Level),
        m_Radius(radius),
        m_Segments(segments),
        m_StartingPosition(position)
    {
        m_AABB.SetScale({ m_Radius * 2.0f, m_Radius * 2.0f });
        m_AABB.SetColor(m_Colour);
        m_Colour = Vector4(1, 0, 0, 1);
        m_LayerMask = ~ObjectType::Metaphysical;
        m_Name = "Ball";
    }

    Ball::~Ball()
    {
        while (!m_SoundWaves.empty())
            m_SoundWaves.pop_back();
    }

    void Ball::Update(float deltaTime)
    {
        //Object::Update(deltaTime);
        //m_AABB.SetPosition(m_Position);
        isCollisionProcessed = false;
        m_AABB.SetScale({m_Radius * 2.0f, m_Radius * 2.0f});
        m_Position += m_Velocity * m_MoveSpeed * deltaTime;
        m_Velocity *= 1 - m_Friction;
        if (m_Velocity.Clamp(m_MaxSpeed))
            m_Velocity = m_Velocity.Normalized() * m_MaxSpeed;
        if (m_Velocity.Length() < 0.7)
            m_Velocity = Vector2::Zero();

        m_AABB.SetPosition(m_Position);
    }

    void Ball::Draw()
    {
        Object::Draw();

    }

    void Ball::OnCollision(CollisionData* data)
    {
        if (isCollisionProcessed)
            return;
        // this is used to pop the object back out of the overlapping object
        Object::OnCollision(data);
        
        // d - 2(d.dot(n) * n)
        float dot = m_Velocity.Dot(data->m_Normal);

        Vector2 reflectedVelocity = m_Velocity - data->m_Normal * (2 * dot);
        m_Velocity = reflectedVelocity * m_DampeningAmount;

        if(data->m_ObjB->GetLayer() == ObjectType::Terrain)
        {
            float duration = 0.1 * m_Velocity.Length();
            duration = fminf(duration, 2.5f);
            m_SoundWaves.push_back(new SoundWave(m_Position, m_Size.x, 100, ".\\TestData\\objHit.wav", duration, m_Level));
        }

    }

    void Ball::Reset()
    {
        m_Position = m_StartingPosition;
        m_Acceleration = Vector2::Zero();
        m_Velocity = Vector2::Zero();

        while (!m_SoundWaves.empty())
            m_SoundWaves.pop_back();

    }

    void Ball::SetRadius(float radius)
    {
        if (radius == m_Radius)
            return;

        m_Radius = radius;
        // modify mesh based on radius
    }

    void Ball::ApplyForce(Vector2 force)
    {
        m_Velocity += force / m_Mass;
    }
    void Ball::CheckOOB()
    {
        // Assuming the bounds are defined by some constants or variables
        const float minX = 0.0f;
        const float maxX = 800.0f; // Example screen width
        const float minY = 0.0f;
        const float maxY = 600.0f; // Example screen height

        if (m_Position.x - m_Radius < minX || m_Position.x + m_Radius > maxX ||
            m_Position.y - m_Radius < minY || m_Position.y + m_Radius > maxY)
        {
            // Ball is out of bounds, handle accordingly
            m_Velocity = Vector2(0, 0); // Stop the ball
            m_Position = Vector2(maxX / 2, maxY / 2); // Reset position to center
        }
    }
}
