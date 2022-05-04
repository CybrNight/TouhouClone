#include "SceneManager.h"
#include "ObjectHandler.h"
#include "AssetManager.h"
#include <SDL_mixer.h>
#include <unordered_map>

namespace CybrEngine {
    Scene* SceneManager::activeScene = nullptr;
    Scene* SceneManager::sceneToLoad = nullptr;
    bool SceneManager::loadNewScene = false;

    std::unordered_map<std::string, Scene*> scenes;
    
    SceneManager::~SceneManager(){

    }

    SceneManager::SceneManager()
    {

    }

    bool SceneManager::CacheScene(std::string name, Scene* scene) {
        auto s = scenes.find(name);
        if (s != scenes.end()){
            return false;
        }
        scenes.insert(std::make_pair(name, scene));
        return true;
    }


    bool SceneManager::LoadScene(std::string name)
    {
        Scene* temp = NULL;
        auto scene = scenes.find(name);

        if (scene != scenes.end()) {
            temp = scene->second;
            //delete activeScene;
            //activeScene = scene;
            loadNewScene = true;
            sceneToLoad = temp;
            ObjectHandler* handler = ObjectHandler::GetInstance();
            AssetManager::GetInstance()->ClearCache();
            handler->DestroyAll();
            return temp->Init();
        }
        return false;
    }

    void SceneManager::Tick() {
        if (loadNewScene) {
            Mix_HaltMusic();
            activeScene = sceneToLoad;
            activeScene->Start();
            loadNewScene = false;
        }

        activeScene->Tick();
    }
    
    void SceneManager::Render(SDL_Renderer* renderer) {
        if (!loadNewScene)
            activeScene->Render(renderer);
    }
}

