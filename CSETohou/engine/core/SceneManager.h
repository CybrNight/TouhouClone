#pragma once
#include "Scene.h"
#include <string>

namespace EngineCore {
    class SceneManager{
    private:
        static Scene* sceneToLoad;
        static Scene* activeScene;
        static bool loadNewScene;

        ~SceneManager();
        SceneManager();
    public:
        static bool Init();

        static bool CacheScene(std::string name, Scene* scene);
        static bool LoadScene(std::string name);
        static void Tick();
        static void Render(SDL_Renderer* renderer);
    };
}


