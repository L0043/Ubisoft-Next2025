#pragma once
#include "stdafx.h"
#include "SoundWave.h"
#include "Level.h"
#include "Map.h"
namespace Echo
{
    //scale.x = radius
    SoundWave::SoundWave(Vector2 position, float radius, float segments, const char* filename, float duration, Level* m_Level, MeshType meshType, ObjectType objType) :
        Object(position, {radius, segments}, 0, { 1,1,1,1 }, meshType, objType, m_Level),
        m_FileName(filename),
        m_InitDuration(duration)
    {
        m_AABB.SetScale({ radius * 2.0f, radius * 2.0f });
        m_LayerMask = ~ObjectType::GolfBall;
        m_Radius = radius;
        m_ColourStep = m_Colour.w / m_InitDuration;
        m_Duration = m_InitDuration;
        App::PlaySoundW(m_FileName);
        m_Level->AddToLayout(this);
    }
    SoundWave::~SoundWave()
    {
        //auto map = m_Level->GetMap();
        
        //m_Level->LoadMap(map);
    }
    void SoundWave::Update(float deltaTime)
    {
        m_Radius += m_Speed * deltaTime;
        m_Mesh.UpdateMesh(m_Radius, m_Size.y);
        m_Duration -= deltaTime;
        m_AABB.SetScale({ m_Radius * 2.0f, m_Radius * 2.0f });
        m_Colour -= deltaTime * m_ColourStep; // Decrease colour by deltaTime * m_Duration
        if (m_Duration <= 0)
        {
            this->Destroy();
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
    void SoundWave::Destroy()
    {
        m_Level->RemoveFromLayout(this);
    }
}