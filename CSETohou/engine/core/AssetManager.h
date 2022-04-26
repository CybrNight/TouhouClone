#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <map>
#include <string>
#include <memory>

class AssetManager
{
    static AssetManager* instance;

    std::shared_ptr<SDL_Renderer> renderer;

    std::map<std::string, SDL_Texture*> spriteCache;
    std::map<std::string, Mix_Music*> musicCache;
    std::map<std::string, Mix_Chunk*> sfxCache;

    SDL_Texture* loadSprite(std::string sprName);
    Mix_Music* loadMusic(std::string musicName, std::string format = "ogg");
    Mix_Chunk* loadSFX(std::string sfxName, std::string format);

public:
    SDL_Texture* getSprite(std::string sprName);
    Mix_Music* getMusic(std::string musicName, std::string format = "ogg");
    Mix_Chunk* getSFX(std::string sfxName);

    int initSprite(std::string sprName);
    int initMusic(std::string musicName, std::string format = "ogg");
    int initSFX(std::string sfxName);

    void clearCache();

    inline void clearSpriteCache()  {spriteCache.clear(); }
    inline void clearMusicCache() {musicCache.clear();  }
    inline void clearSFXCache() {sfxCache.clear(); }

    static inline AssetManager* getAssetManager(){ return instance; }

    AssetManager(std::shared_ptr<SDL_Renderer> renderer);
    ~AssetManager();
};

