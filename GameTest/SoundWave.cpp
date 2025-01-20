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
        m_Radius = radius;
        App::PlaySoundW(m_fileName);
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
       
        if(m_Timer >= m_Duration)
        {
            this->~SoundWave();
        }

    }
    void SoundWave::Draw()
    {
        Object::Draw();
    }
    void SoundWave::OnCollision(CollisionData* data)
    {
    }
}