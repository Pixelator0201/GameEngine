// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

#include "Engine.h"
#include <Player.h>
#include <Enemy.h>
#include <fmod.hpp>
#include "Assets.h"
#include "File.h"

using namespace nu;
int main()
{
    // get current working directory
    std::cout << "Directory Operations:\n";
    std::cout << "Working directory: " << nu::GetWorkingDirectory() << "\n";

    // set working directory (current working directory + "Assets")
    std::cout << "Setting directory to 'Assets'...\n";
    nu::SetWorkingDirectory("Assets");
    std::cout << "New directory: " << nu::GetWorkingDirectory() << "\n\n";

    // get filenames in the working directory
    std::cout << "Files in Directory:\n";
    auto filenames = nu::GetFilesInDirectory(nu::GetWorkingDirectory());
    for (const auto& filename : filenames)
    {
        std::cout << filename << "\n";
    }
    std::cout << "\n";

    // get filename info
    if (!filenames.empty())
    {
        // get filename
        std::string str = nu::GetFilename(filenames[0]);
        std::cout << "Filename: " << str << "\n";

        // get extension
        str = nu::GetFileExtension(filenames[0]);
        std::cout << "Extension: " << str << "\n";

        // get filename no extension
        str = nu::GetFilenameNoExtension(filenames[0]);
        std::cout << "Filename No Extension: " << str << "\n\n";
    }

    // read and display text file
    std::cout << "Text File Reading:\n";
    std::string str;
    if (nu::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }

    // write to text file
    std::cout << "Text File Writing:\n";
    nu::WriteTextFile("test.txt", "Hello, World!", true);
    if (nu::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }


    // INITIALIZATION
    Engine::Get().Initialize();

    // create audio system
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    std::vector<FMOD::Sound*> sounds;


    

    //std::vector<Vector2> points{ Vector2{ -3, 3 }, Vector2{ 3, 3 } };

    Scene scene;

    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.model = assets::playerModel;
    playerDesc.transform = Transform{ Vector2{ 640.0f, 512.0f }, 0.0f, 15.0f };
    playerDesc.velocity = Vector2{ 0.0f, 0.0f };
    playerDesc.speed = 2000.0f;

    Player* player = new Player{ playerDesc };
    scene.AddActor(player);
    
    for (int i = 0; i < 20; i++)
    {
        EnemyDesc enemyDesc;
        enemyDesc.name = "Enemy";
        enemyDesc.model = assets::enemyModel;
        enemyDesc.transform = Transform{ Vector2{ nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWidth()),
            nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetHeight())}, 90.0f, 10.0f };
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
        Engine::Get().Update();

        float dt = Engine::Get().GetTime().GetDeltaTime();
                
        scene.Update(dt);
        audio->update();
                

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
            audio->playSound(sounds[0], nullptr, false, nullptr);
        }

        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_2))
        {
            audio->playSound(sounds[1], nullptr, false, nullptr);
        }

        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_3))
        {
            audio->playSound(sounds[2], nullptr, false, nullptr);
        }

        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_4))
        {
            audio->playSound(sounds[3], nullptr, false, nullptr);
        }

        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_5))
        {
            audio->playSound(sounds[4], nullptr, false, nullptr);
        }

        // RENDER
        Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f, 255);
        Engine::Get().GetRenderer().Clear();

        for (int i = 0; i < (int)points.size() - 1; i++) {
            Engine::Get().GetRenderer().SetColor(1.0f, 1.0f, 1.0f);

            //points[i] = points[i] + vel;
            Engine::Get().GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        //character
        //player.Draw(Engine::Get().GetRenderer());
        //enemy.Draw(Engine::Get().GetRenderer());
        scene.Draw(Engine::Get().GetRenderer());
        //renderer.SetColor(1.0f, 1.0f, 1.0f);
        //renderer.DrawFillRect(position.x - 20, position.y - 20, 40, 40);

        Engine::Get().GetRenderer().Present(); // Render the screen


    }

    // SHUTDOWN
    

    return 0;
    //fnEngine();
}

