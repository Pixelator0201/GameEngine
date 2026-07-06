// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SDL3/SDL.h"
#include "Engine.h"

int main()
{
    nu::Renderer renderer;
    renderer.Initialize("Game Engine", 1280, 1024);

    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }


        renderer.SetColor(0, 0, 0, 255);
        renderer.Clear();

        for (int i = 0; i < 1000; i++) {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 255);
            renderer.DrawPoint(rand() % 1280, rand() % 1024);
        }
        for (int i = 0; i < 10; i++) {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 255);
            renderer.DrawLine(rand() % 1280, rand() % 1024, rand() % 1280, rand() % 1024);
        }

        for (int i = 0; i < 5; i++) {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
            renderer.DrawFillRect(rand() % 1280, rand() % 1024, rand() % 500, rand() % 500);
        }

        renderer.Present(); // Render the screen
    }

    renderer.Shutdown();

    return 0;
    //fnEngine();
}

