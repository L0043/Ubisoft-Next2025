#pragma once
#include "stdafx.h"
#include "SoundWave.h"

namespace Echo
{
    //scale.x = radius
    SoundWave::SoundWave(Vector2 position, float radius, float segments, const char* filename, float duration, Level* m_Level, MeshType meshType, ObjectType objType) :
        Object(position, {radius, segments}, 0, { 1,1,1,1 }, meshType, objType, m_Level),
        m_fileName(filename),
        m_Duration(duration)
    {
        m_AABB.SetScale({ radius * 2.0f, radius * 2.0f });
        m_LayerMask = ~ObjectType::GolfBall;
        m_Radius = radius;
        App::PlaySoundW(m_fileName);
        isDebug = true;
    }
    SoundWave::~SoundWave()
    {
        delete m_fileName;
    }
    void SoundWave::Update(float deltaTime)
    {
        m_Radius += m_Speed * deltaTime;
        m_Mesh.UpdateMesh(m_Radius, m_Size.y);
        m_Timer += deltaTime;
        m_AABB.SetScale({ m_Radius * 2.0f, m_Radius * 2.0f });
        if(m_Timer >= m_Duration)
        {
            //this->~SoundWave();
            //delete this object
        }

    }
    void SoundWave::Draw()
    {
        Object::Draw();
    }
    void SoundWave::OnCollision(CollisionData* data)
    {
        if(data->m_ObjB->GetLayer() == ObjectType::Terrain)
        {
            //m_Radius = 0.0f;
        }
    }
}