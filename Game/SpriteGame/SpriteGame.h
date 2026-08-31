#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"
#include "Resources/ResourceManager.h"

class SpriteGame : public nu::Game
{
public:
	enum class GameState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		GameOver
	};

public:
	SpriteGame() = default;
	SpriteGame(nu::Scene* scene) :
		Game{ scene } 
	{	}

	bool Initialize();

	void Update(float dt) override;
	void Draw(class nu::Renderer& renderer) override;

	void OnPlayerDead();
	void AddPoints(int points) { m_score += points; }
	void SetHealth(int health) { m_health = health; }
private:
	void SpawnPlayer();
	void SpawnEnemy();

	int m_score{ 0 };
	int m_lives{ 0 };

	float m_stateTimer{ 0.0f };

	float m_spawnTimer{ 0.0f };
	float m_spawnTime{ 5.0f };
	int m_spawnCount{ 0 };
	int m_health = 0;

	GameState m_gameState = GameState::Title;

	nu::res_t<nu::Font> titleFont;
	nu::res_t<nu::Font> gameOverFont;
	nu::res_t<nu::Font> gameFont;

	//nu::Font* titleFont{ nullptr };
	nu::Text* titleText{ nullptr };

	//nu::Font* gameOverFont{ nullptr };
	nu::Text* gameOverText{ nullptr };

	//nu::Font* gameFont{ nullptr };
	nu::Text* scoreText{ nullptr };
	nu::Text* livesText{ nullptr };
	nu::Text* healthText{ nullptr };
};