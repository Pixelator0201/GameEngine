// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <random>
#include <fstream>

#include "Engine.h"
#include "SpaceGame/Player.h"
#include "SpaceGame/Enemy.h"
#include <fmod.hpp>
#include "SpaceGame/Assets.h"
#include "Core/File.h"
#include "SpaceGame/SpaceGame.h"
#include "SpriteGame/SpriteGame.h"
#include "SpaceGame/Bullet.h"



using namespace nu;

int main()
{
    // Stay.
    SetWorkingDirectory("Assets/SpaceGame");

    //Factory::Instance().Register<Actor>("Actor");
    //Factory::Instance().Register<Object>("Object");
    //Factory::Instance().Register<Player>("Player");
    //Factory::Instance().Register<Enemy>("Enemy");
    //Factory::Instance().Register<Bullet>("Bullet");
    /*

    auto actor = Factory::Instance().Create<Actor>("Actor");
    auto object = Factory::Instance().Create("Object");

    std::cout << actor->IsActive() << std::endl;
    std::cout << object->IsActive() << std::endl;

    auto player = Factory::Instance().Create<Player>("Player");

    json::document_t document;
    if (json::Load("data/scene.json", document))
    {
        player->Read(document);
        std::cout << player->GetName() << std::endl;
        std::cout << player->GetTag() << std::endl;
                     
        std::cout << player->GetTransform().rotation << std::endl;
        std::cout << player->GetSpeed() << std::endl;
    }

    return 0;
    */
        
       
        // INITIALIZATION
    Engine::Get().Initialize();

    std::unique_ptr game = std::make_unique<SpriteGame>();
    game->Initialize();

    

    Vector2 position{ 640.0f, 512.0f };
    Vector2 velocity{ 0.0f, 0.0f };
    
    
    std::vector<Vector2> points;

    // create texture, using shared_ptr so texture can be shared
    //std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    //texture->Load("textures/player.png", Engine::Get().GetRenderer());

        //auto texture = Resources().Get<Texture>("textures/background.png", Engine::Get().GetRenderer());
        //Engine::Get().GetRenderer().DrawTexture(*texture, 0, 0, 0.0f, 10.0f);
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
         
        game->Update(dt);
                            

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

        game->Draw(Engine::Get().GetRenderer());

        for (int i = 0; i < (int)points.size() - 1; i++) {
            Engine::Get().GetRenderer().SetColor(1.0f, 1.0f, 1.0f);

            //points[i] = points[i] + vel;
            Engine::Get().GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        
        
        
        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

        // Draw Texture

        Engine::Get().GetRenderer().Present(); // Render the screen


    }

    game.reset();

    // SHUTDOWN
    Engine::Get().Shutdown();

    return 0;
    //fnEngine();
}

