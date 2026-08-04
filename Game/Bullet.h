#pragma once
#include "Actor.h"

struct BulletDesc : public nu::ActorDesc
{
    float speed;
};

class Bullet : public nu::Actor
{
public:
    Bullet() = default;
    Bullet(const BulletDesc& bulletDesc) :
        Actor(bulletDesc),
        m_speed{ bulletDesc.speed }
    {
    }
    
    void Update(float dt) override;
private:
    float m_speed = 800.0f;
};