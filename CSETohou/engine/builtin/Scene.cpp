#include "Scene.h"
#include "ObjectHandler.h"
#include "AssetManager.h"
#include <SDL_mixer.h>
#include <iostream>

bool Scene::Init()
{
    EngineCore::ObjectHandler* oHandler = EngineCore::ObjectHandler::GetInstance();
    if (LoadSceneAssets()) {
        return true;
    }
    else {
        std::cout << "Game: Failed to initialize scene assets\n";
    }
    return false;
}
