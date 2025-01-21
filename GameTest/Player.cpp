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
        m_Rotation(rotation),
        m_Mesh(type, m_Position, m_Colour, m_Rotation,size.x, size.y)
    {
        m_Name = "Club";
    }
    Player::~Player()
    {

    }
    void Player::Update(float deltaTime)
    {
        Input();

        // rotate to face the ball
        Vector2 ballPos = m_Ball.GetPosition();
        Vector2 direction = ballPos - m_Position;
        float angle = atan2f(direction.y, direction.x);
        m_Rotation = angle * (180.0f / PI);
        m_Mesh.SetRotation(m_Rotation);
    }
    void Player::Draw()
    {
        m_Mesh.Draw();
        if (text)
        {
            App::Print(20, APP_INIT_WINDOW_HEIGHT - 20, "Charging Shot");
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
        float len = m_Ball.GetVelocity().Length();
        if (len > 1)
            return;
         
        if (App::IsKeyPressed(VK_SPACE) == true)
        {
            m_ChargeForce += 1.f;
            text = true;
            wasPressedLastFrame = true;
            //App::PlaySoundW("") play a tone with increasing pitch
            // if player releases the button, apply the force to the ball.
        }
        if (App::IsKeyPressed(VK_SPACE) == false && wasPressedLastFrame)
        {
            //apply force to the ball
            float force = fminf(m_ChargeForce, m_ChargeForceLimit);
            Vector2 dis = -distance.Normalized();
            m_Ball.ApplyForce(dis * force);
            App::PlaySoundW(".\\TestData\\clubHit.wav");
            m_Strokes++;
            // reset the force
            m_ChargeForce = 0.0f;
            text = false;
            wasPressedLastFrame = false;
        }

    }
}
