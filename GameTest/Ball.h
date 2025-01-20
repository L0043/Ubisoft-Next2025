#pragma once
#include "stdafx.h"
#include "Object.h"

#include <vector>
namespace Echo 
{
    class SoundWave;
    class Ball : public Object
	{
	public:
		Ball(Vector2 position, float radius, int segments, Level* m_Level, MeshType type = MeshType::Circle, ObjectType objType = ObjectType::ball );
		~Ball();
        virtual void Update(float deltaTime) override;
        virtual void Draw() override;
        virtual void OnCollision(CollisionData* data) override;
        void SetRadius(float radius);
        void SetMass(float mass) { m_Mass = mass; };
        void SetFriction(float friction) { m_Friction = friction; };
        void ApplyForce(Vector2 force);
        void CheckOOB();
        float GetRadius() const { return m_Radius; };
        Vector2 GetVelocity() const { return m_Velocity; };
	private:
        std::vector<SoundWave*> m_SoundWaves;
        const int m_Segments;
        float m_Radius;
        float m_Mass = 1;
        float m_Friction = 0.01f;
        float m_MoveSpeed = 10;
        float m_MaxSpeed = 50;
        Vector2 m_Velocity;
        Vector2 m_Acceleration;
        bool initCollide = false;
	};
}