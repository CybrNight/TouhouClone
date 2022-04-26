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
    void render();
    
    // Called every frame
    void tick();

    void start();
    bool loadGameAssets(AssetManager* aManager);

};