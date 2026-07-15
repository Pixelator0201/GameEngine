#pragma once
#include "Actor.h"

class Player : public nu::Actor
{
public:
    Player() = default;
    Player(float speed, const nu::Transform& transform) : Actor{ transform }, m_speed{ speed } {}
    Player(float speed, const nu::Transform& transform, const nu::Model& model) : Actor{ transform, model }, m_speed{ speed } {}

    void Update(float dt) override;
    void Draw(const nu::Renderer& renderer) const override;
private:
    int m_ammo = 0;
    float m_speed = 800.0f;
};