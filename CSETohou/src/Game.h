#pragma once

#include <SDL.h>
#include "AssetManager.h"

class GameObject;

class ObjectHandler;


class Game {
    static Game* instance;


    void Init(std::shared_ptr<SDL_Renderer> renderer);

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