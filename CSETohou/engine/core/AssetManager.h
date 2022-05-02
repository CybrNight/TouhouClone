#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <string>
#include <memory>
#include <unordered_map>
#include "Defs.h"

using std::unique_ptr;

namespace EngineCore {
    class AssetManager {
        //Static instance to self
        static AssetManager* instance;

        //Store pointer to shared renderer from main
        std::shared_ptr<SDL_Renderer> renderer;

        //Maps that pair the name of the 
        std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> spriteCache;
        std::unordered_map<std::string, Mix_Music*> musicCache;
        std::unordered_map<std::string, Mix_Chunk*> sfxCache;

        SDL_Texture* LoadSprite(std::string sprName);
        Mix_Music* LoadMusic(std::string musicName, std::string format = "ogg");
        Mix_Chunk* LoadSFX(std::string sfxName, std::string format);

        void Init(std::shared_ptr<SDL_Renderer> renderer);

        AssetManager() {}
        ~AssetManager();
    public:
        /// <summary>
        /// Retrieve static reference to AssetManager
        /// </summary>
        /// <param name="renderer"></param>
        /// <returns></returns>
        static AssetManager* GetInstance(std::shared_ptr<SDL_Renderer> renderer = nullptr);

        /// <summary>
        /// Retreive pre-loaded texture from memory 
        /// </summary>
        /// <param name="sprName"></param>
        /// <returns></returns>
        std::shared_ptr<SDL_Texture> GetCachedSprite(std::string sprName);

        /// <summary>
        /// Retrieve previously loaded music from memory
        /// </summary>
        /// <param name="musicName"></param>
        /// <param name="format"></param>
        /// <returns></returns>
        Mix_Music* GetCachedMusic(std::string musicName, std::string format = "ogg");

        /// <summary>
        /// Retrieve pre-loaded music from memory
        /// </summary>
        /// <param name="sfxName"></param>
        /// <returns></returns>
        Mix_Chunk* GetCachedSFX(std::string sfxName);

        /// <summary>
        /// Load sprite from file and save to memory
        /// </summary>
        /// <param name="sprName"></param>
        /// <returns></returns>
        bool CacheSprite(std::string sprName);

        /// <summary>
        /// Load music from file and save to memory
        /// </summary>
        /// <param name="musicName"></param>
        /// <param name="format"></param>
        /// <returns></returns>
        bool CacheMusic(std::string musicName, std::string format = "ogg");

        /// <summary>
        /// Load SFX from file and save to memory
        /// </summary>
        /// <param name="sfxName"></param>
        /// <returns></returns>
        bool CacheSFX(std::string sfxName);

        //Deletes all cached assets
        void ClearCache();

        //Deletes all cached sprites
        inline void ClearSpriteCache() { spriteCache.clear(); }

        //Clears all music from cache
        inline void ClearMusicCache() { musicCache.clear(); }

        //Clears all SFX from cache
        inline void ClearSFXCache() { sfxCache.clear(); }
    };
}

