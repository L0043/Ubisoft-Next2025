#pragma once
#include "stdafx.h"
#include "Object.h"
class CSimpleSprite;
class CController;
namespace Echo
{
	class Ball;
    // this class is going to be the golf club, it will have a sprite(may be wireframe) and an AABB
    // the player will be able to move the golf ball by hitting it with this object.
	class Player
	{
	public:
		// not sure if im going to have the player be wireframe or sprite yet.
		Player(Vector2 position, Vector2 size, float rotation, Ball* ball, MeshType type = MeshType::Rect, CSimpleSprite* sprite = nullptr);
		~Player();
        void Update(float deltaTime);
        void Draw();
		void Input();
	private:
		// base class variables
		
		CSimpleSprite* m_Sprite;
		Mesh m_Mesh;
		Vector2 m_Position;
		Vector2 m_Size;
		Vector4 m_Colour;
		std::string m_Name = "";
		float m_ChargeForce = 0.0f;
		const float m_ChargeForceLimit = 100.0f;
		const float m_MaxDistance = 50.0f;
		Ball& m_Ball;
		bool text;
		bool wasPressedLastFrame;
	};
}