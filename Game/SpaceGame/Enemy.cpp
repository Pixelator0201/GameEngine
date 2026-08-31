#include "pch.h"
#include "Enemy.h"
#include "Renderer/Render.h"
#include "Engine.h"
#include "Player.h"
#include "SpaceGame.h"
#include "Components/PhysicsComponent.h"

FACTORY_REGISTER(Enemy)

void Enemy::Update(float dt)
{
    Player* player = m_scene->GetActorByName<Player>("PlayerPrototype");
    if (player)
    {

        auto physicsComponent = GetComponent<nu::PhysicsComponent>();
        nu::Vector2 forward{ 1, 0 }; // ->
        if (physicsComponent)
        {
            nu::Vector2 force = forward.Rotate(m_transform.rotation * nu::DegToRad) * m_speed;
            physicsComponent->ApplyForce(force);

            nu::Vector2 direction = player->GetTransform().position - m_transform.position;
            float rotation = direction.Angle();
            physicsComponent->SetRotation(rotation * nu::RadToDeg);

            nu::Vector2 position = physicsComponent->GetPosition();

            position.x = nu::Wrap(0.0f, 1280.0f, position.x);
            position.y = nu::Wrap(0.0f, 1024.0f, position.y);
            physicsComponent->SetPosition(position);
        }
    }

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
            particle.texture = nu::Resources().Get<nu::Texture>("textures/bullet.png", nu::Engine::Get().GetRenderer());
            particle.lifespan = 1.0f;
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

