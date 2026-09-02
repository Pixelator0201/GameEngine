#include "pch.h"
#include "Player.h"
#include "Renderer/Render.h"
#include "Engine.h"
#include "Bullet.h"
#include "Assets.h"
#include "SpaceGame.h"
#include "Components/PhysicsComponent.h"


class RegisterPlayer {
public: RegisterPlayer() {
    nu::Factory::Instance().Register<Player>("Player");
}
}; static RegisterPlayer registerInstance;

void Player::Update(float dt)
{
    // Movement
    float thrust = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = m_speed;

    float rotate = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -80.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = 80.0f;

    auto physicsComponent = GetComponent<nu::PhysicsComponent>();
    nu::Vector2 forward{ 1, 0 }; // ->
    if (physicsComponent)
    {
        nu::Vector2 force = forward.Rotate(m_transform.rotation * nu::DegToRad) * thrust;
        physicsComponent->ApplyForce(force);

        physicsComponent->ApplyTorque(rotate);

        nu::Vector2 position = physicsComponent->GetPosition();

        //position.x = nu::Wrap(0.0f, 1280.0f, position.x);
        //position.y = nu::Wrap(0.0f, 1024.0f, position.y);
        //physicsComponent->SetPosition(position);

        nu::Engine::Get().GetRenderer().SetCamera(position);
    }



    //AddVelocity(velocity * dt);

    // Warp
    if (warp_cooldown <= 0)
    {
        if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_TAB))
        {
            warp_cooldown = 5.0f;
            m_transform.position += forward.Rotate(m_transform.rotation * nu::DegToRad) * 300;
        }
    }
    else {
        warp_cooldown -= dt;
    }

    ((SpaceGame*)m_scene->GetGame())->SetHealth(m_health);

    // Fire
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_1)) bulletType = 1;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_2)) bulletType = 2;
    if (bulletType == 1) {
        if (fire_cooldown <= 0)
        {
            if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
            {
                fire_cooldown = 0.25f;

                auto bullet = nu::Factory::Instance().Create<Bullet>("BulletPrototype");
                bullet->SetTransform(m_transform);
                bullet->SetScale(2.0f);
                bullet->SetTag("PlayerBullet");
                m_scene->AddActor(std::move(bullet));

            }
        }
        else {
            fire_cooldown -= dt;
        }
    }

    if (bulletType == 2) {
        if (fire_cooldown <= 0)
        {
            if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
            {
                fire_cooldown = 2.0f;
                auto bullet = nu::Factory::Instance().Create<Bullet>("BulletPrototype");
                bullet->SetTransform(m_transform);
                bullet->SetScale(2.0f);
                bullet->SetTag("PlayerBullet");
                m_scene->AddActor(std::move(bullet));

                //BulletDesc desc;
                //desc.name = "Bullet";
                //desc.tag = "PlayerBullet";
               
                //desc.transform = m_transform;
                ////desc.transform.scale *= 15.0f;
                //desc.speed = 1000.0f;
                //desc.lifespan = 2.0f;
                //
                //m_scene->AddActor(std::make_unique<Bullet>(desc));

                //desc.transform.rotation += 10.0f;
                //m_scene->AddActor(std::make_unique<Bullet>(desc));

                //desc.transform.rotation -= 20.0f;
                //m_scene->AddActor(std::make_unique<Bullet>(desc));

            }
        }
        else {
            fire_cooldown -= dt;
        }
    }
    // Bullet time
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_X))
    {
        nu::Engine::Get().GetTime().SetTimeScale(0.5f);
    }
    else
    {
        nu::Engine::Get().GetTime().SetTimeScale(1.0f);
    }

    nu::Particle particle;

    nu::Vector2 offset{ -10.0f, 0.0f };
    offset = offset.Rotate(m_transform.rotation * nu::DegToRad);

    nu::Color colors[3] = { { 1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 0.0f} };
    particle.position = m_transform.position + offset;
    particle.color = colors[nu::RandomInt(3)];
    particle.texture = nu::Resources().Get<nu::Texture>("textures/bullet.png", nu::Engine::Get().GetRenderer());
    particle.lifespan = 1.0f;
    particle.velocity = nu::Vector2{ -nu::RandomFloat(-30.0f, -100.0f), 0.0f }.Rotate((m_transform.rotation + nu::RandomInt(-30, 30)) * nu::DegToRad);

    if (m_health <= 0)
    {
        SetDestroyed();
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

    nu::Engine::Get().GetPS().AddParticle(particle);

    Actor::Update(dt);
}



void Player::OnCollision(Actor* other)
{
    if (other->GetTag() == "Enemy")
    {
        m_health -= 25;
        
        other->SetDestroyed();
        if (m_health <= 0)
        {
            SetDestroyed();
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
            ((SpaceGame*)m_scene->GetGame())->OnPlayerDead();
        }

        for (int i = 0; i < 100; i++)
        {
            nu::Particle particle;
            particle.position = other->GetTransform().position;
            particle.color = { 1.0f, 1.0f, 1.0f };
            particle.texture = nu::Resources().Get<nu::Texture>("textures/bullet.png", nu::Engine::Get().GetRenderer());
            particle.lifespan = 1.0f;
            particle.velocity = { nu::RandomFloat(-600.0f, 600.0f), nu::RandomFloat(-600.0f, 600.0f) };

            nu::Engine::Get().GetPS().AddParticle(particle);
        }
    }
}

void Player::Read(const nu::json::value_t& value)
{
    Actor::Read(value);

    JSON_READ_NAME(value, "speed", m_speed);
}

