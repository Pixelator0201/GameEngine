#pragma once

#include "Random.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Transform.h"
#include "MathUtils.h"
#include "Game.h"
#include "Text.h"

// Systems
#include "Render.h"
#include "Input.h"
#include "GameTime.h"
#include "Audio.h"
#include "ParticleSystem.h"
#include "Actor.h"
#include "Scene.h"
#include "Texture.h"
#include "ResourceManager.h"

namespace nu
{
	class Engine
	{
	public:
		static Engine& Get() { static Engine engine; return engine; }

		bool Initialize();
		void Shutdown();

		void Update();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }
		Time& GetTime() { return m_time; }
		Audio& GetAudio() { return m_audio; }
		ParticleSystem& GetPS() { return m_particleSystem; }


	private:
		Engine() = default;

	private:
		Input m_input;
		Renderer m_renderer;

		Time m_time;
		Audio m_audio;
		ParticleSystem m_particleSystem;

	};

	
}