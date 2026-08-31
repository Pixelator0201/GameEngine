#include "pch.h"
#include "Game.h"
#include "Scene.h"

namespace nu
{
	Game::Game() = default;
	Game::~Game() = default;

	void Game::Update(float dt)
	{
		m_scene->Update(dt);
	}
	void Game::SetScene(std::unique_ptr<Scene> scene)
	{
		m_scene = std::move(scene);
	}

	void Game::Draw(Renderer& renderer)
	{
		m_scene->Draw(renderer);
	}
}
