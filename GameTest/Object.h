#pragma once
#include "stdafx.h"
#include "AABB.h" 
class CSimpleSprite;
namespace Echo
{
    struct CollisionData;
    class Level;
    enum ObjectType : uint32_t
    {
        GolfBall        = 1 << 0,
        Terrain         = 1 << 1,
        Interactible    = 1 << 2,
        Metaphysical    = 1 << 3
    };

	class Object
	{
	public:
        // sprites might want to be optional, as such I have made it a pointer so it can be null in the constructor
        Object(Vector2 position, Vector2 size, float rotation, Vector4 colour, MeshType type, ObjectType objType, Level* level,CSimpleSprite* sprite = nullptr);
		~Object();
        virtual void Update(float deltaTime);
        virtual void Draw();
        virtual void OnCollision(CollisionData* data);
        void SetPosition(Vector2 position) { m_Position = position; };
        void SetSize(Vector2 size) { m_Size = size; };
        void SetRotation(Vector2 rotation) { m_Rotation = rotation; };
        void SetSprite(CSimpleSprite* sprite) { m_Sprite = sprite; };
        void SetColour(Vector4 colour) { m_Colour = colour; };
        void SetMesh(Mesh mesh) { m_Mesh = mesh; };
        void SetStatic(bool stat) { isStatic = stat; }
        void SetLayerMask(uint32_t type) { m_LayerMask = type; }
        void SetLayer(ObjectType type) { m_Layer = type; }
        Vector2 GetPosition() const { return m_Position; };
        Vector2 GetSize()const { return m_Size; };
        Vector2 GetRotation()const { return m_Rotation; };
        Vector4 GetColour()const { return m_Colour; };
        AABB GetAABB()const { return m_AABB; };
        Mesh GetMesh()const { return m_Mesh; };
        CSimpleSprite* GetSprite()const { return m_Sprite; };
        uint32_t GetLayerMask() const { return m_LayerMask; }
        ObjectType GetLayer() const { return m_Layer; }
        bool IsStatic() const { return isStatic; }

        std::string m_Name = "";
	protected:
        CSimpleSprite* m_Sprite;
        Level* m_Level;
        uint32_t m_LayerMask;
        ObjectType m_Layer;
        AABB m_AABB;
        Mesh m_Mesh;
        Vector2 m_Position;
        Vector2 m_Size;
        Vector2 m_Rotation;
        Vector4 m_Colour;
        bool isStatic = false;
        bool isDebug = false;
        bool isCollisionProcessed;
	};
}
