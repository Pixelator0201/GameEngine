#pragma once
#include "Actor.h"

struct PlayerDesc : public nu::ActorDesc
{
    float speed = 0.0f;
};

class Player : public nu::Actor
{
public:
    Player() = default;
    Player(const PlayerDesc& playerDesc) :
        Actor{ playerDesc },
        m_speed{ playerDesc.speed }
    { }

    CLASS_PROTOTYPE(Player)
    
    void Update(float dt) override;
    void OnCollision(Actor* other);

    virtual void Read(const nu::json::value_t& value) override;

    float GetSpeed() const { return m_speed; }

    int GetHealth() const { return m_health; }
private:
    int m_ammo = 0;
    float m_speed = 800.0f;
    float warp_cooldown = 0.0f;
    float fire_cooldown = 0.0f;
    int m_health = 100;

    int bulletType = 1;
};