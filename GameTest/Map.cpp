#include "stdafx.h"
#include "Map.h"

namespace Echo
{
    Map::Map()
    {
    }

    Map::~Map()
    {
    }
    // this func became hazardous the moment I decided to make Objects require a reference to the level.
    //void Map::CreateGeometry(MeshType meshType, ObjectType objType, Vector2 position, Vector2 args, Vector4 colour, float rotation)
    //{
    //    if(!m_pLevel)
    //        return
    //    Object obj = { position, args, rotation, colour, meshType, objType, *m_pLevel};
    //    m_Geometry.push_back(&obj);
    //}
}
