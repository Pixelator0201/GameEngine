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

    Vector2 vel{ 0.5f, 0.0f };
    std::vector<Vector2> v;

    for (int i = 0; i < 300; i++) 
    {
        v.push_back(Vector2{ RandomFloat(1280), RandomFloat(1024) });
    }

    // MAIN LOOP
    bool quit = false;
    while (!quit) {

        // UPDATE
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        // RENDER
        renderer.SetColor(0.0f, 0.0f, 0.0f, 255);
        renderer.Clear();

        for (size_t i = 0; i < v.size(); i++) {
            renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat());

            v[i] = v[i] + vel;
            renderer.DrawPoint(v[i].x, v[i].y);
        }
        //for (int i = 0; i < 10; i++) {
        //    renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat());
        //    renderer.DrawLine(RandomFloat(1280), RandomFloat(1024), RandomFloat(1280), RandomFloat(1024));
        //}

        //for (int i = 0; i < 5; i++) {
        //    renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat());
        //    renderer.DrawFillRect(RandomFloat(1280), RandomFloat(1024), RandomFloat(500), RandomFloat(500));
        //}

        renderer.Present(); // Render the screen
    }

    // SHUTDOWN
    renderer.Shutdown();

    return 0;
    //fnEngine();
}

