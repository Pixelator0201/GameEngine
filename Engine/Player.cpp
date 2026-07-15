#include "pch.h"
#include "Player.h"
#include "Render.h"
#include "Engine.h"

void Player::Update(float dt)
{
    nu::Vector2 force{ 0.0f, 0.0f };
    if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_A)) force.x = -m_speed;
    if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_D)) force.x = m_speed;
    if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_S)) force.y = m_speed;
    if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_W)) force.y = -m_speed;

    SetVelocity(GetVelocity() + (force * dt));

    Actor::Update(dt);
}

void Player::Draw(const nu::Renderer& renderer) const
{
	Actor::Draw(renderer);
}
