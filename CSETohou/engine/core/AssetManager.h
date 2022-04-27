#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <string>
#include <memory>
#include <unordered_map>
#include "Defs.h"

using std::unique_ptr;

class AssetManager
{
    static AssetManager* instance;

    std::shared_ptr<SDL_Renderer> renderer;

    std::vector<std::string> loadQueue;

    std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> spriteCache;
    std::unordered_map<std::string, Mix_Music*> musicCache;
    std::unordered_map<std::string, Mix_Chunk*> sfxCache;

    SDL_Texture* LoadSprite(std::string sprName);
    Mix_Music* LoadMusic(std::string musicName, std::string format = "ogg");
    Mix_Chunk* LoadSFX(std::string sfxName, std::string format);

public:
    SDL_Texture* GetCachedSprite(std::string sprName);
    Mix_Music* GetCachedMusic(std::string musicName, std::string format = "ogg");
    Mix_Chunk* GetCachedSFX(std::string sfxName);

    bool CacheSprite(std::string sprName);
    bool CacheMusic(std::string musicName, std::string format = "ogg");
    bool CacheSFX(std::string sfxName);

    void clearCache();

    inline void ClearSpriteCache()  {spriteCache.clear(); }
    inline void ClearMusicCache() {musicCache.clear();  }
    inline void ClearSFXCache() {sfxCache.clear(); }

    static inline AssetManager* GetAssetManager(){ return instance; }

    AssetManager(std::shared_ptr<SDL_Renderer> renderer);
    ~AssetManager();
};

