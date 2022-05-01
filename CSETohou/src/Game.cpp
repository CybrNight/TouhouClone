#include "Game.h"
#include "ObjectHandler.h"
#include "Player.h"
#include "Defs.h"
#include <iostream>
#include "BasicEnemy.h"
#include "EnemySpawner.h"
#include "BurstEnemy.h"
#include <SDL_mixer.h>
#include "AssetManager.h"

float Time::DELTA_TIME;
float Time::SECOND;

Game* Game::instance;

Game::Game()
{
    
}

void Game::Tick() {
    
}

void Game::Init(std::shared_ptr<SDL_Renderer> renderer) {
    this->renderer = renderer;
}

Game* Game::GetInstance(std::shared_ptr<SDL_Renderer> renderer)
{
    if (instance == NULL) {
        instance = new Game();
        instance->Init(renderer);
    }
    return instance;

}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer.get(), 79, 0, 129, 128);
    SDL_RenderFillRectF(renderer.get(), new SDL_FRect{ 0, 0, MIN_X, SCREEN_HEIGHT });
    SDL_RenderFillRectF(renderer.get(), new SDL_FRect{ 0, MAX_Y, SCREEN_WIDTH, SCREEN_HEIGHT });
    SDL_RenderFillRectF(renderer.get(), new SDL_FRect{ 0, 0, SCREEN_WIDTH, MIN_Y });
    SDL_RenderFillRectF(renderer.get(), new SDL_FRect{ MAX_X, 0, SCREEN_WIDTH, SCREEN_HEIGHT });

}

bool Game::Start() {
    EngineCore::ObjectHandler* oHandler = EngineCore::ObjectHandler::GetInstance();
    if (LoadGameAssets()){
        Mix_Music* music = EngineCore::AssetManager::GetInstance()->GetCachedMusic("bgm01");

        if (Mix_PlayingMusic() == 0) {
            Mix_PlayMusic(music, -1);

            std::cout << "Game: start()\n";
            oHandler->Instantiate(new Player(GAME_WIDTH / 2, GAME_HEIGHT - GRID_SIZE * 2));
            oHandler->Instantiate(new EnemySpawner());
        }

        return true;
    }
    else {
        std::cout << "Game: Failed to initialize game assets\n";
    }
}

bool Game::LoadGameAssets()
{
    EngineCore::AssetManager* temp = EngineCore::AssetManager::GetInstance();
    int check = 0;

    check -= temp->CacheSprite("sprPlayer");
    check -= temp->CacheSprite("sprEnemy");
    check -= temp->CacheSprite("sprTrishotEnemy");
    check -= temp->CacheSprite("sprBurstEnemy");
    check -= temp->CacheMusic("bgm01", "ogg");

    return check != 0;
}
