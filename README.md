# Game Engine - Sprite Game

This is the game engine for my Intro to Game Programming class, written in C++ and using Box2D for physics, and a simple platformer game built within it.

The Engine has implemented:
- A renderer system to draw to the screen
- A components system mainly including components to support rendering and components to support physics
- An Audio system
- A Physics system
- A Factory system to implement actors
- The Game

The game is an incredibly simple platformer where the goal is to jump around the stage and kill enemies to gain score. 
<img width="642" height="536" alt="image" src="https://github.com/user-attachments/assets/148cd577-bf08-45ec-9476-9b3e2e4c4bf0" />

The controls are:
- A and D to move left and right
- Space to jump
- Right Shift to attack

The game is incredibly simple and has some issues such as sprites incorrectly clipping into the floor and infinite jumps.
<img width="642" height="536" alt="Screenshot 2026-09-03 214731" src="https://github.com/user-attachments/assets/f50e5ce7-7d46-4a08-955a-a5b4ff1b6809" />

The game utilizes the "Free Pixel Art Forest" asset by edermunizz on itch.io for the background, linked here: https://edermunizz.itch.io/free-pixel-art-forest
