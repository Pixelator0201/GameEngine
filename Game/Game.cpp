// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

#include "Engine.h"
#include <Player.h>

using namespace nu;





int main()
{
    // INITIALIZATION
    engine.Initialize();

    //std::vector<Vector2> points{ Vector2{ -3, 3 }, Vector2{ 3, 3 } };
    Mesh mesh{ { Vector2{ 2, 0 }, Vector2{ -2, 2 }, Vector2{ -1, 0 }, Vector2{2, 0}, Vector2{-2, -2}, Vector2{-1, 0} }, Color{ 0.0f, 0.0f, 1.0f } };

    Player player{ 2000.0f, Transform{ Vector2{ 640.0f, 512.0f }, 0.0f, 15.0f }, std::vector<Mesh>{ mesh } };

    Vector2 position{ 640.0f, 512.0f };
    Vector2 velocity{ 0.0f, 0.0f };
    
    
    std::vector<Vector2> points;

    //uint64_t ticks = SDL_GetTicksNS();
    //uint64_t prevTicks = ticks;

    //for (int i = 0; i < 300; i++) 
    //{
    //    v.push_back(Vector2{ RandomFloat(1280), RandomFloat(1024) });
    //}


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

        //player.SetRotation(90.0f);
        player.SetRotation(player.GetTransform().rotation + (90.0f * engine.GetTime().GetDeltaTime()));

        player.Update(engine.GetTime().GetDeltaTime());

        /* 
        //prevTicks = ticks;
        //ticks = SDL_GetTicksNS(); // 1'000'000'000 ticks = 1 second
        //float seconds = (float)ticks / 1'000'000'000;
        //float dt = (float)(ticks - prevTicks) / 1'000'000'000;
        //std::cout << seconds << " " << dt << std::endl;

        //if (input.GetKeyPressed(SDL_SCANCODE_Q)) std::cout << "pressed\n";
        //if (input.GetKeyDown(SDL_SCANCODE_Q)) std::cout << "down\n";
        //if (input.GetKeyReleased(SDL_SCANCODE_Q)) std::cout << "released\n";

        //if (input.GetButtonPressed(Input::MouseButton::Left)) std::cout << "Button Pressed\n";
        
        //if (keyState[SDL_SCANCODE_SPACE]) std::cout << "press\n";
        */

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

        

        //velocity += (force * time.GetDeltaTime());
        //position += (velocity * time.GetDeltaTime());

        //position.x = Wrap(0.0f, 1280.0f, position.x);
        //position.y = Wrap(0.0f, 1024.0f, position.y);

        // RENDER
        engine.GetRenderer().SetColor(0.0f, 0.0f, 0.0f, 255);
        engine.GetRenderer().Clear();

        for (int i = 0; i < (int)points.size() - 1; i++) {
            engine.GetRenderer().SetColor(1.0f, 1.0f, 1.0f);

            //points[i] = points[i] + vel;
            engine.GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        //character
        player.Draw(engine.GetRenderer());
        //renderer.SetColor(1.0f, 1.0f, 1.0f);
        //renderer.DrawFillRect(position.x - 20, position.y - 20, 40, 40);

        engine.GetRenderer().Present(); // Render the screen
        //for (int i = 0; i < 10; i++) {
        //    renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat());
        //    renderer.DrawLine(RandomFloat(1280), RandomFloat(1024), RandomFloat(1280), RandomFloat(1024));
        //}

        //for (int i = 0; i < 5; i++) {
        //    renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat());
        //    renderer.DrawFillRect(RandomFloat(1280), RandomFloat(1024), RandomFloat(500), RandomFloat(500));
        //}

    }

    // SHUTDOWN
    

    return 0;
    //fnEngine();
}

