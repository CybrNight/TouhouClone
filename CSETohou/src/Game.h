#pragma once

#include <SDL.h>
#include "AssetManager.h"

class GameObject;

class ObjectHandler;


class Game {
    static Game* instance;


    void Init(std::shared_ptr<SDL_Renderer> renderer);

    SDL_FRect left{ 0, 0, MIN_X, SCREEN_HEIGHT };
    SDL_FRect right{ 0, MAX_Y, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_FRect up{ 0, 0, SCREEN_WIDTH, MIN_Y };
    SDL_FRect down{ MAX_X, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    Game();
    ~Game() {}

public:
    std::shared_ptr<SDL_Renderer> renderer;

    static Game* GetInstance(std::shared_ptr<SDL_Renderer> renderer = nullptr);

    // Called every time the window is re-drawn
    void Render();
    
    // Called every frame
    void Tick();

    bool Start();
    bool LoadGameAssets();

};