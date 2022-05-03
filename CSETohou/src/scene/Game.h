#pragma once

#include <SDL.h>
#include "AssetManager.h"
#include "Input.h"
#include "UILabel.h"
#include "Scene.h"
#include <iostream>

class GameObject;

class ObjectHandler;


class Game: public virtual Scene {
    int volume = 32;

    SDL_FRect left{ 0, 0, MIN_X, SCREEN_HEIGHT };
    SDL_FRect right{ 0, MAX_Y, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_FRect up{ 0, 0, SCREEN_WIDTH, MIN_Y };
    SDL_FRect down{ MAX_X, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    std::shared_ptr<UI::UILabel> volumeLabel = nullptr;
    Mix_Music* music = nullptr;


public:
    Game();
    ~Game() { std::cout << "Destroyed Game\n"; }

    // Called every time the window is re-drawn
    void Render(SDL_Renderer* renderer);
    
    // Called every frame
    void Tick();
    bool Start();
    bool LoadSceneAssets();

};