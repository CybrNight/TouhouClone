#pragma once
#include "Object.h"
#include <vector>
#include <SDL.h>

class Scene {

public:
    bool Init();
    virtual void Tick() = 0;
    virtual void Render(SDL_Renderer* renderer) = 0;
    virtual bool Start() = 0;
    virtual bool LoadSceneAssets() = 0;
};

