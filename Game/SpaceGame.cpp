#include "SpaceGame.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include <memory>

using namespace nu;
bool SpaceGame::Initialize()
{
	Game::Initialize();

	m_scene = new Scene();
	m_scene->SetGame(this);
	m_scene->Load("data/scene.json");

	

	Engine::Get().GetAudio().AddSound("alert", "alert.mp3");

	//titleFont = Resources().Get<Font>("Fonts/Orbitron-VariableFont_wght.ttf", 64);
	//titleFont->Load("Fonts/Orbitron-VariableFont_wght.ttf", 64);

	
	//Resources().Get<Texture>("textures/player.png", Engine::Get().GetRenderer());


	titleText = new Text(Resources().GetWithID<Font>("title_font", "Fonts/Orbitron-VariableFont_wght.ttf", 64.0f));
	titleText->Create(Engine::Get().GetRenderer(), "Totally Original Space Game (tm)", Color{ 1.0f, 1.0f, 1.0f });

	//gameOverFont = std::make_shared<Font>();
	//gameOverFont->Load("Fonts/Orbitron-VariableFont_wght.ttf", 64);
	
	gameOverText = new Text(Resources().GetWithID<Font>("game_font", "Fonts/Orbitron-VariableFont_wght.ttf", 64.0f));
	gameOverText->Create(Engine::Get().GetRenderer(), "Game Over....", Color{ 1.0f, 1.0f, 1.0f });

	//gameFont = Resources().Get<Font>("Fonts/Orbitron-VariableFont_wght.ttf", 32);
	//gameFont->Load("Fonts/Orbitron-VariableFont_wght.ttf", 32);

	scoreText = new Text(Resources().Get<Font>("Fonts/Orbitron-VariableFont_wght.ttf", 32.0f));
	livesText = new Text(Resources().Get<Font>("Fonts/Orbitron-VariableFont_wght.ttf", 32.0f));
	healthText = new Text(Resources().Get<Font>("Fonts/Orbitron-VariableFont_wght.ttf", 32.0f));

	

	return false;
}

void SpaceGame::Update(float dt)
{
	switch (m_gameState)
	{
	case SpaceGame::GameState::Title:
		if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
			m_gameState = GameState::StartGame;
		break;
	case SpaceGame::GameState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_spawnTime = 5.0f;
		m_stateTimer = 1.0f;
		
		m_gameState = GameState::StartLevel;
		break;
	case SpaceGame::GameState::StartLevel:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene->RemoveAllActors();
			SpawnPlayer();
			m_spawnTime = 5.0f;
			m_gameState = GameState::Game;
			m_stateTimer = 2.0f;
		}

		break;
	case SpaceGame::GameState::Game:
		m_spawnTimer -= dt;
		if (m_spawnTimer <= 0)
		{
			m_spawnTimer = m_spawnTime;
			SpawnEnemy();
			m_spawnCount++;
			if (m_spawnCount > 5)
				m_spawnTime -= 0.5f;
			m_spawnCount = 0;
		}
		break;
	case SpaceGame::GameState::GameOver:
		m_scene->RemoveAllActors();
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_gameState = GameState::Title;
		}
		break;
	default:
		break;

	}

	Game::Update(dt);
}

void SpaceGame::Draw(nu::Renderer& renderer)
{
	renderer.DrawTexture(*nu::Resources().Get<Texture>("textures/background.png", Engine::Get().GetRenderer()), 500, 500, 0.0f, 2.0f);

	switch (m_gameState)
	{
	case SpaceGame::GameState::Title:
		// draw Title
		titleText->Draw(renderer, 100, 400);
		break;
	case SpaceGame::GameState::StartGame:
	case SpaceGame::GameState::StartLevel:
	case SpaceGame::GameState::Game:
		//draw score / lives
		scoreText->Create(renderer, "Score: " + std::to_string(m_score), Color{ 1.0f, 1.0f, 1.0f });
		scoreText->Draw(renderer, 30, 30);
		livesText->Create(renderer, "Lives: " + std::to_string(m_lives), Color{ 1.0f, 1.0f, 1.0f });
		livesText->Draw(renderer, renderer.GetWidth() - 160.0f, 30);
		healthText->Create(renderer, "Health: " + std::to_string(m_health), Color{ 1.0f, 1.0f, 1.0f });
		healthText->Draw(renderer, 30, 60);
		break;
	case SpaceGame::GameState::GameOver:
		//draw game over
		gameOverText->Draw(renderer, 400, 400);
		break;
	default:
		break;

	}
	Game::Draw(renderer);
}

void SpaceGame::OnPlayerDead()
{
	m_lives--;
	if (m_lives <= 0) m_gameState = GameState::GameOver;
	else m_gameState = GameState::StartLevel;
}

void SpaceGame::SpawnPlayer()
{
	auto actor = Factory::Instance().Create<Actor>("PlayerPrototype");
	actor->SetPosition(nu::Vector2{ 30.0f, 30.0f });

	m_scene->AddActor(std::move(actor));
}

void SpaceGame::SpawnEnemy()
{
	auto actor = Factory::Instance().Create<Actor>("EnemyPrototype");
	actor->SetPosition({ nu::RandomFloat(1024.0f), nu::RandomFloat(800.0f) });
	m_scene->AddActor(std::move(actor));
	/*
	EnemyDesc enemyDesc;
	enemyDesc.name = "Enemy";
	enemyDesc.name = "Enemy";
	enemyDesc.texture = Resources().Get<Texture>("textures/enemy.png", Engine::Get().GetRenderer());
	//enemyDesc.model = assets::enemyModel;
	enemyDesc.transform = Transform{ Vector2{ nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWidth()),
		nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetHeight())}, 90.0f, 1.0f };
	enemyDesc.damping = 3.0f;
	enemyDesc.speed = RandomFloat(1000.0f, 2000.0f);

	m_scene->AddActor(std::make_unique<Enemy>(enemyDesc));
	*/
}
