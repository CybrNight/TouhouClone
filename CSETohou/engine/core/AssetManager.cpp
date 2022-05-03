#include "AssetManager.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

namespace CybrEngine {
    AssetManager* AssetManager::sceneToLoad;

    SDL_Texture* AssetManager::LoadSprite(std::string sprName) {
        // The final texture
        SDL_Texture* newTexture = NULL;

        //Try to load sprite with name from sprite directory
        SDL_Surface* loadedSurface = IMG_Load(("resource/sprite/" + sprName + ".png").c_str());
        if (loadedSurface == NULL) {
            printf("Unable to load image %s! SDL_image Error: %s\n",
                sprName.c_str(),
                IMG_GetError());
        }
        else {
            // After loading image create texture from surface pixels
            newTexture = SDL_CreateTextureFromSurface(renderer.get(), loadedSurface);
            if (newTexture == NULL) {
                printf("Unable to create texture from %s! SDL Error: %s\n",
                    sprName.c_str(),
                    SDL_GetError());
            }

            // Cleanup the loaded surface
            SDL_FreeSurface(loadedSurface);
        }

        //Print status message and return the sprite
        std::cout << "AssetManager: Loaded new sprite (" << sprName << ") from file. Returned to AssetManger\n";
        return newTexture;
    }

    Mix_Music* AssetManager::LoadMusic(std::string musicName, std::string format) {
        //Try to load music with name and format from music resource directory
        Mix_Music* music = Mix_LoadMUS(("resource/music/" + musicName + '.' + format).c_str());
        if (music == NULL) {
            std::cout << "Failed to load music from resource/music/" << musicName << '.' << format << '\n';
        }

        return music;
    }

    void AssetManager::Init(std::shared_ptr<SDL_Renderer> renderer)
    {
        this->renderer = renderer;
    }

    std::shared_ptr<SDL_Texture> AssetManager::GetCachedSprite(std::string sprName) {
        auto temp = spriteCache.find(sprName);
        if (temp != spriteCache.end()) {
            std::cout << "AssetManager: Retrieved sprite (" << sprName << ") from spriteCache\n";
            return (*temp).second;
        }
        else {
            std::cout << "AssetManager: Did not find sprite (" << sprName << ") in spriteCache\n";
            if (CacheSprite(sprName)) {
                GetCachedSprite(sprName);
            }
            else {
                std::cout << "AssetManager: Failed to add sprite (" << sprName << ") to spriteCache\n";
            }
        }

        return NULL;
    }

    Mix_Music* AssetManager::GetCachedMusic(std::string musicName, std::string format) {
        auto temp = musicCache.find(musicName);
        Mix_Music* tempMusic = NULL;
        if (temp != musicCache.end()) {
            std::cout << "AssetManager: Retrieved " << musicName << " from musicCache\n";
            tempMusic = (*temp).second;
        }
        else {
            std::cout << "AssetManager: Did not find music (" << musicName << ") in musicCache\n";
            tempMusic = LoadMusic(musicName);
            musicCache.insert(std::make_pair(musicName, tempMusic));
            std::cout << "AssetManager: Added music (" << musicName << ") to musicCache\n";
        }
        return tempMusic;
    }

    Mix_Chunk* AssetManager::GetCachedSFX(std::string sfxName) {
        return nullptr;
    }

    bool AssetManager::CacheSprite(std::string sprName) {

        std::cout << "AssetManager: Initialzing sprite (" << sprName << ")\n";

        std::shared_ptr<SDL_Texture> temp = std::shared_ptr<SDL_Texture>(LoadSprite(sprName), SDL_DestroyTexture);

        if (temp == NULL) {
            std::cout << "AssetManager: Failed to load sprite (" << sprName << ")\n";
            return false;
        }

        spriteCache.insert(std::make_pair(sprName, temp));
        std::cout << "AssetManager: Added sprite (" << sprName << ") to spriteCache\n";

        return true;
    }

    bool AssetManager::CacheMusic(std::string musicName, std::string format) {
        std::cout << "AssetManager: Initializing music (" << musicName << ")\n";
        Mix_Music* tempMusic = LoadMusic(musicName, format);
        if (tempMusic == NULL) {
            return false;
        }

        musicCache.insert(std::make_pair(musicName, tempMusic));
        std::cout << "AssetManager: Added sprite (" << musicName << ") to spriteCache\n";
        return true;
    }

    void AssetManager::ClearCache() {
        ClearSpriteCache();
        ClearMusicCache();
        ClearSFXCache();
    }

    AssetManager::~AssetManager() {
        ClearCache();
    }

    AssetManager* AssetManager::GetInstance(std::shared_ptr<SDL_Renderer> renderer){
        if (sceneToLoad == NULL) {
            sceneToLoad = new AssetManager();
            sceneToLoad->Init(renderer);
        }
        return sceneToLoad;
    }
}