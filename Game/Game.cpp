// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

#include "Engine.h"

using namespace nu;





int main()
{
    // INITIALIZATION
    nu::Renderer renderer;
    renderer.Initialize("Game Engine", 1280, 1024);
    
    //std::cout << sizeof(Vector2) << std::endl;
    nu::Input input;
    input.Initialize();

    Time time;

    //std::vector<Vector2> points{ Vector2{ -3, 3 }, Vector2{ 3, 3 } };
    Mesh mesh{ { Vector2{ -3, 3 }, Vector2{ 3, 3 }, Vector2{ 0, 0 } }, Color{ 0.0f, 0.0f, 1.0f } };

    Actor player{ Transform{ Vector2{ 640.0f, 512.0f }, 0.0f, 50.0f }, std::vector<Mesh>{ mesh } };

    Vector2 position{ 640.0f, 512.0f };
    Vector2 velocity{ 0.0f, 0.0f };
    float speed = 400.0f;
    
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
        input.Update();
        time.Tick();


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

        Vector2 mousePosition;
        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

        if (input.GetMouseDown(Input::MouseButton::Left))
        {
            if (points.empty())
            {
                points.push_back(input.GetMousePosition());
            }

            Vector2 v = points.back() - input.GetMousePosition();

            if (v.Length() > 10.0f)
            {
                points.push_back(input.GetMousePosition());
            }
        }

        // undo
        if (input.GetButtonPressed(Input::MouseButton::Right))
        {
            if (points.empty()) points.pop_back();
        }

        Vector2 force{ 0.0f, 0.0f };

        if (input.GetKeyDown(SDL_SCANCODE_A)) force.x = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_D)) force.x = speed;
        if (input.GetKeyDown(SDL_SCANCODE_S)) force.y = speed;
        if (input.GetKeyDown(SDL_SCANCODE_W)) force.y = -speed;

        player.SetVelocity(player.GetVelocity() + (force * time.GetDeltaTime()));
        player.Update(time.GetDeltaTime());

        //velocity += (force * time.GetDeltaTime());
        //position += (velocity * time.GetDeltaTime());

        //position.x = Wrap(0.0f, 1280.0f, position.x);
        //position.y = Wrap(0.0f, 1024.0f, position.y);

        // RENDER
        renderer.SetColor(0.0f, 0.0f, 0.0f, 255);
        renderer.Clear();

        for (int i = 0; i < (int)points.size() - 1; i++) {
            renderer.SetColor(1.0f, 1.0f, 1.0f);

            //points[i] = points[i] + vel;
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        //character
        player.Draw(renderer);
        //renderer.SetColor(1.0f, 1.0f, 1.0f);
        //renderer.DrawFillRect(position.x - 20, position.y - 20, 40, 40);

        renderer.Present(); // Render the screen
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
    renderer.Shutdown();

    return 0;
    //fnEngine();
}

