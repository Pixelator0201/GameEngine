#pragma once

#include "Core/Random.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"
#include "Math/MathUtils.h"
#include "Framework/Game.h"
#include "Renderer/Text.h"
#include "Core/StringUtils.h"
#include "Core/Factory.h"
#include "Serialization/JSON.h"

// Systems
#include "Renderer/Render.h"
#include "Input/Input.h"
#include "Core/GameTime.h"
#include "Audio/Audio.h"
#include "Renderer/ParticleSystem.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Renderer/Texture.h"
#include "Resources/ResourceManager.h"
#include "Physics/Physics.h"

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
		Physics& GetPhysics() { return m_physics; }

	private:
		Engine() = default;

	private:
		Input m_input;
		Renderer m_renderer;
		Physics m_physics;

		Time m_time;	
		Audio m_audio;
		ParticleSystem m_particleSystem;

	};

	
}