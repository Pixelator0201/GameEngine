// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

#include "Engine.h"
#include <Player.h>
#include <Enemy.h>
#include <fmod.hpp>


using namespace nu;
int main()
{
    // INITIALIZATION
    engine.Initialize();

    // create audio system
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    std::vector<FMOD::Sound*> sounds;


    

    //std::vector<Vector2> points{ Vector2{ -3, 3 }, Vector2{ 3, 3 } };
    Mesh mesh{ { Vector2{ 2, 0 }, Vector2{ -2, 2 }, Vector2{ -1, 0 }, Vector2{-2, -2}, Vector2{2, 0} }, Color{ 0.0f, 0.0f, 1.0f } };
    Mesh mesh2{ { Vector2{ 0, 1 }, Vector2{ -3, 5 }, Vector2{ 2, 0 }, Vector2{ -3, -5 }, Vector2{ 0, -1 } }, Color{ 255, 255, 0 } };
    Model model{ std::vector<Mesh>{ mesh, mesh2 } };

    Scene scene;

    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.model = model;
    playerDesc.transform = Transform{ Vector2{ 640.0f, 512.0f }, 0.0f, 15.0f };
    playerDesc.velocity = Vector2{ 0.0f, 0.0f };
    playerDesc.speed = 2000.0f;

    Player* player = new Player{ playerDesc };
    scene.AddActor(player);
    
    for (int i = 0; i < 20; i++)
    {
        EnemyDesc enemyDesc;
        enemyDesc.name = "Enemy";
        enemyDesc.model = model;
        enemyDesc.transform = Transform{ Vector2{ nu::RandomFloat((float)nu::engine.GetRenderer().GetWidth()),
            nu::RandomFloat((float)nu::engine.GetRenderer().GetHeight())}, 90.0f, 10.0f };
        enemyDesc.speed = 2000.0f;

        Enemy* enemy = new Enemy{ enemyDesc };
        scene.AddActor(enemy);
    }

    Vector2 position{ 640.0f, 512.0f };
    Vector2 velocity{ 0.0f, 0.0f };
    
    
    std::vector<Vector2> points;

    /* i don't remember what this one was
    //uint64_t ticks = SDL_GetTicksNS();
    //uint64_t prevTicks = ticks;

    //for (int i = 0; i < 300; i++) 
    //{
    //    v.push_back(Vector2{ RandomFloat(1280), RandomFloat(1024) });
    //}
    */

    FMOD::Sound* sound = nullptr;
    audio->createSound("test.wav", FMOD_DEFAULT, 0, &sound);

    audio->playSound(sound, 0, false, nullptr);

    audio->createSound("whistle.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("alert.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("error.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("hee-hee.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("scream.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

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
        engine.Update();

        float dt = engine.GetTime().GetDeltaTime();
                
        scene.Update(dt);
        audio->update();
                

        Vector2 mousePosition;
        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

        if (engine.GetInput().GetMouseDown(Input::MouseButton::Left))
        {
            if (points.empty())
            {
                points.push_back(engine.GetInput().GetMousePosition());
            }

            Vector2 v = points.back() - engine.GetInput().GetMousePosition();

            if (v.Length() > 10.0f)
            {
                points.push_back(engine.GetInput().GetMousePosition());
            }
        }

        // undo
        if (engine.GetInput().GetButtonPressed(Input::MouseButton::Right))
        {
            if (!points.empty()) points.pop_back();
        }

       // Keyboard sounds
        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_1))
        {
            audio->playSound(sounds[0], nullptr, false, nullptr);
        }

        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_2))
        {
            audio->playSound(sounds[1], nullptr, false, nullptr);
        }

        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_3))
        {
            audio->playSound(sounds[2], nullptr, false, nullptr);
        }

        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_4))
        {
            audio->playSound(sounds[3], nullptr, false, nullptr);
        }

        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_5))
        {
            audio->playSound(sounds[4], nullptr, false, nullptr);
        }

        // RENDER
        engine.GetRenderer().SetColor(0.0f, 0.0f, 0.0f, 255);
        engine.GetRenderer().Clear();

        for (int i = 0; i < (int)points.size() - 1; i++) {
            engine.GetRenderer().SetColor(1.0f, 1.0f, 1.0f);

            //points[i] = points[i] + vel;
            engine.GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        //character
        //player.Draw(engine.GetRenderer());
        //enemy.Draw(engine.GetRenderer());
        scene.Draw(engine.GetRenderer());
        //renderer.SetColor(1.0f, 1.0f, 1.0f);
        //renderer.DrawFillRect(position.x - 20, position.y - 20, 40, 40);

        engine.GetRenderer().Present(); // Render the screen


    }

    // SHUTDOWN
    

    return 0;
    //fnEngine();
}

