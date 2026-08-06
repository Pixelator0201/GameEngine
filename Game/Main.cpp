// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <random>

#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include <fmod.hpp>
#include "Assets.h"
#include "File.h"
#include "SpaceGame.h"



using namespace nu;

class Object
{
public:
    Object() { std::cout << "constructor\n"; }
    ~Object() { std::cout << "destructor\n"; }

    Object(const Object& object) { std::cout << "copy\n"; }
    Object& operator = (const Object& object) { std::cout << "assignment\n"; return *this; }

};

uint32_t seed = 1234;

uint32_t RNG()
{
    seed = (seed * 1103515245) + 12345;
    return seed;
}

int main()
{
    SetWorkingDirectory("Assets");
      


    // INITIALIZATION
    Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();

    

    Vector2 position{ 640.0f, 512.0f };
    Vector2 velocity{ 0.0f, 0.0f };
    
    
    std::vector<Vector2> points;

    // create texture, using shared_ptr so texture can be shared
    //std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    //texture->Load("textures/player.png", Engine::Get().GetRenderer());

    // MAIN LOOP
    bool quit = false;
    while (!quit) {

        // UPDATE
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)
            {
                quit = true;
            }
        }

        // engine
        Engine::Get().Update();

        float dt = Engine::Get().GetTime().GetDeltaTime();

        game.Update(dt);
                            

        Vector2 mousePosition;
        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

        if (Engine::Get().GetInput().GetMouseDown(Input::MouseButton::Left))
        {
            if (points.empty())
            {
                points.push_back(Engine::Get().GetInput().GetMousePosition());
            }

            Vector2 v = points.back() - Engine::Get().GetInput().GetMousePosition();

            if (v.Length() > 10.0f)
            {
                points.push_back(Engine::Get().GetInput().GetMousePosition());
            }
        }

        // undo
        if (Engine::Get().GetInput().GetButtonPressed(Input::MouseButton::Right))
        {
            if (!points.empty()) points.pop_back();
        }

       // Keyboard sounds
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_1))
        {
            Engine::Get().GetAudio().PlaySound("alert");
        }

        // RENDER
        Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f, 255);
        Engine::Get().GetRenderer().Clear();

        game.Draw(Engine::Get().GetRenderer());

        for (int i = 0; i < (int)points.size() - 1; i++) {
            Engine::Get().GetRenderer().SetColor(1.0f, 1.0f, 1.0f);

            //points[i] = points[i] + vel;
            Engine::Get().GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        
        
        
        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

        // Draw Texture
        auto texture = Resources().Get<Texture>("textures/player.png", Engine::Get().GetRenderer());
        Engine::Get().GetRenderer().DrawTexture(*texture, 30, 30, 23.0f, 2.0f);

        Engine::Get().GetRenderer().Present(); // Render the screen


    }

    // SHUTDOWN
    Engine::Get().Shutdown();

    return 0;
    //fnEngine();
}

