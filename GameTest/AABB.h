#pragma once
#include "stdafx.h"
namespace Echo
{
	class AABB
	{
	public:
		AABB(Vector2 position, float width, float height, Vector4 colour);
		~AABB();
        void Update();
        void Draw();
        void SetPosition(Vector2 position);
        void SetScale(Vector2 scale);
        void SetColor(Vector4 colour) { m_Colour = colour; };
        Vector2 GetPosition() const { return m_Position; };
        Vector2 GetScale() const { return m_Scale; };
        Vector2 GetMin() const { return m_Min; };
        Vector2 GetMax() const { return m_Max; };
        Vector4 GetColor() const { return m_Colour; };
        std::pair<Vector2, float> GetCollisionNormal(const AABB& other);
        bool Overlaps(AABB& other);
	private:
        // these variables feel like they should be public, 
        // but thats probably just because I'm used to Unity.
        Vector2 m_Position;
        Vector2 m_Scale;
		// Bottom Left of the AABB
        Vector2 m_Min;
        // Top Right of the AABB
        Vector2 m_Max;
        Vector4 m_Colour;
        //const float m_LineThickness = 6;
	};
}