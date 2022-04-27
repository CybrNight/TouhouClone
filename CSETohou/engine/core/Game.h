#pragma once

#include <SDL.h>
#include "AssetManager.h"

class GameObject;

class ObjectHandler;


class Game {

public:
    std::shared_ptr<SDL_Renderer> renderer;

    Game(std::shared_ptr<SDL_Renderer> renderer);
    ~Game(){}

    // Called every time the window is re-drawn
    void Render();
    
    // Called every frame
    void Tick();

    bool Start();
    bool LoadGameAssets();

};