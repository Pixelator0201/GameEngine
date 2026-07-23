#include "pch.h"
#include "Player.h"
#include "Render.h"
#include "Engine.h"
#include "Bullet.h"
#include "Assets.h"

void Player::Update(float dt)
{
    // Movement
    float thrust = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = m_speed;

    float rotate = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = 180.0f;

    SetRotation(m_transform.rotation + rotate * dt);

    nu::Vector2 forward{ 1, 0 }; // ->
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegToRad) * thrust;
    AddVelocity(velocity * dt);

    // Fire
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
    {
        BulletDesc desc;
        desc.name = "Bullet";
        desc.tag = "Bullet";
        desc.model = assets::bulletModel;
        desc.transform = m_transform,
        desc.speed = 1000.0f;
        desc.lifespan = 2.0f;

        Bullet* bullet = new Bullet{ desc };
        m_scene->AddActor(bullet);
    }

    Actor::Update(dt);
}

