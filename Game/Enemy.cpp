#include "pch.h"
#include "Enemy.h"
#include "Render.h"
#include "Engine.h"
#include "Player.h"
#include "SpaceGame.h"

FACTORY_REGISTER(Enemy)

void Enemy::Update(float dt)
{
    Player* player = m_scene->GetActorByName<Player>("PlayerPrototype");
    if (player)
    {
        nu::Vector2 direction = player->GetTransform().position - m_transform.position;
        float rotation = direction.Angle();
        SetRotation(rotation * nu::RadToDeg);

        nu::Vector2 forward{ 1, 0 };
        forward = forward.Rotate(m_transform.rotation * nu::DegToRad);
        AddVelocity(forward * m_speed * dt);
    }

    float thrust = 0.0f;
    //if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;
    //if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = m_speed;

    float rotate = 0.0f;
    //if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
    //if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = 180.0f;

    //SetRotation(m_transform.rotation + rotate * dt);

    nu::Vector2 forward{ 1, 0 }; // ->
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegToRad) * thrust;
    AddVelocity(velocity * dt);

    //SetVelocity(GetVelocity() + (force * dt));

    Actor::Update(dt);
}

void Enemy::OnCollision(Actor* other)
{
    if (other->GetTag() == "PlayerBullet")
    {
        SetDestroyed();
        other->SetDestroyed();

        ((SpaceGame*)m_scene->GetGame())->AddPoints(100);
        

        // create particle explosion
        for (int i = 0; i < 100; i++)
        {
            nu::Particle particle;
            particle.position = m_transform.position;
            particle.color = { 1.0f, 1.0f, 1.0f };
            particle.lifespan = nu::RandomFloat(0.5f, 2.0f);
            particle.velocity = { nu::RandomFloat(-600.0f, 600.0f), nu::RandomFloat(-600.0f, 600.0f) };

            nu::Engine::Get().GetPS().AddParticle(particle);
        }
    }
}

void Enemy::Read(const nu::json::value_t& value)
{
    Actor::Read(value);

    JSON_READ_NAME(value, "speed", m_speed);
}

