#pragma once

#include <SDL.h>
#include "AssetManager.h"
#include "Input.h"
#include "UILabel.h"
#include "Scene.h"

class GameObject;

class ObjectHandler;


class Game2: public virtual Scene {

    int volume = 32;

    SDL_FRect left{ 0, 0, MIN_X, SCREEN_HEIGHT };
    SDL_FRect right{ 0, MAX_Y, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_FRect up{ 0, 0, SCREEN_WIDTH, MIN_Y };
    SDL_FRect down{ MAX_X, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_Rect drawRect;
    SDL_Rect boundsRect;

    std::shared_ptr<UI::UILabel> volumeLabel = NULL;
    std::shared_ptr<SDL_Texture> background = NULL;


public:
    Game2();
    ~Game2() {}

    // Called every time the window is re-drawn
    void Render(SDL_Renderer* renderer);
    
    // Called every frame
    void Tick();
    bool Start();
    bool LoadSceneAssets();

};
