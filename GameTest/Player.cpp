#include "stdafx.h"
#include "Player.h"
#include "App/app.h"
#include <corecrt_math.h>
#include "Ball.h"
namespace Echo
{
    Player::Player(Vector2 position, Vector2 size, float rotation, Ball* ball, MeshType type, CSimpleSprite* sprite):
        m_Colour({ 1,0,1,1 }),
        m_Position(position),
        m_Size(size),
        m_Ball(*ball),
        m_Mesh(type, m_Position, m_Colour, size.x, size.y)
    {
        m_Name = "Club";
        
    }
    Player::~Player()
    {

    }
    void Player::Update(float deltaTime)
    {
        Input();
    }
    void Player::Draw()
    {
        m_Mesh.Draw();
        if (text)
        {
            App::Print(200, 100, "Charging");
        }
    }
    void Player::Input()
    {
        // this will be made so the player can change the force applied to the ball depending on duration the button is held.
        Vector2 direction = Vector2(0, 0);
        float mouseX, mouseY;
        App::GetMousePos(mouseX, mouseY);

        const Vector2 ballPos = m_Ball.GetPosition();
        // limit club to a certain distance from the ball
        Vector2 distance = Vector2(0, 0);
        distance = Vector2(mouseX, mouseY) - ballPos; // ballpos
        distance.Normalize();
        distance *= m_MaxDistance;

        // clamp the distance to the max distance
        Vector2 result = Vector2(fminf(distance.x, m_MaxDistance), fminf(distance.y, m_MaxDistance));

        m_Position = ballPos + result;

         
        if (App::IsKeyPressed('L') == true)
        {
            m_ChargeForce += 1.f;
            text = true;
            wasPressedLastFrame = true;
            // if player releases the button, apply the force to the ball.
        }
        if (App::IsKeyPressed('L') == false && wasPressedLastFrame)
        {
            //apply force to the ball
            float force = fminf(m_ChargeForce, m_ChargeForceLimit);
            Vector2 dis = -distance.Normalized();
            m_Ball.ApplyForce(dis * force);
            // reset the force
            m_ChargeForce = 0.0f;
            text = false;
            wasPressedLastFrame = false;
        }

    }
}
