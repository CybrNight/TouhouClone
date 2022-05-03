#include "SceneManager.h"
#include "ObjectHandler.h"
#include <SDL_mixer.h>
#include <unordered_map>

namespace EngineCore {
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
            delete scene;
            return false;
        }
        scenes.insert(std::make_pair(name, scene));
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
            handler->DestroyAll();
            return temp->Init();
        }
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

