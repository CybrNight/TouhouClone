#include "Scene.h"
#include "ObjectHandler.h"
#include "AssetManager.h"
#include <SDL_mixer.h>
#include <iostream>

bool Scene::Init()
{
    CybrEngine::ObjectHandler* oHandler = CybrEngine::ObjectHandler::GetInstance();
    if (LoadSceneAssets()) {
        return true;
    }
    else {
        std::cout << "Game: Failed to initialize scene assets\n";
    }
    return false;
}
