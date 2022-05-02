#include "Game.h"
#include "ObjectHandler.h"
#include "Player.h"
#include "Defs.h"
#include <iostream>
#include "BasicEnemy.h"
#include "EnemySpawner.h"
#include "BurstEnemy.h"
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using EngineCore::Input;

float Time::DELTA_TIME;
float Time::SECOND;

using UI::UILabel;

Game* Game::instance;

Game::Game()
{
    
}

void Game::Tick() {
    Input* input = Input::GetInstance();

    if (input->GetKey(SDL_SCANCODE_MINUS)) {
        volume--;

        if (volume < 0)
            volume = 0;

        Mix_VolumeMusic(volume);
    }
    
    if (input->GetKey(SDL_SCANCODE_EQUALS)) {
        volume++;

        if (volume > 128)
            volume = 128;

        Mix_VolumeMusic(volume);
    }

    volumeLabel->SetText("Volume:" + std::to_string(volume));
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
    SDL_RenderFillRectF(renderer.get(), &left);
    SDL_RenderFillRectF(renderer.get(), &right);
    SDL_RenderFillRectF(renderer.get(), &up);
    SDL_RenderFillRectF(renderer.get(), &down);
}

bool Game::Start() {
    EngineCore::ObjectHandler* oHandler = EngineCore::ObjectHandler::GetInstance();
    if (LoadGameAssets()){
        Mix_Music* music = EngineCore::AssetManager::GetInstance()->GetCachedMusic("bgm01");

        if (Mix_PlayingMusic() == 0) {
            Mix_PlayMusic(music, -1);
            Mix_VolumeMusic(volume);

            std::cout << "Game: start()\n";
            oHandler->Instantiate(new Player(GAME_WIDTH / 2, GAME_HEIGHT - GRID_SIZE * 2));
            oHandler->Instantiate(new EnemySpawner());
            volumeLabel = dynamic_cast<UILabel*>(oHandler->Instantiate(new UILabel(MAX_X+GRID_SIZE*2, GRID_SIZE*8, 128, 32, "Volume")));
        }

        return true;
    }
    else {
        std::cout << "Game: Failed to initialize game assets\n";
        return false;
    }
}

bool Game::LoadGameAssets()
{
    EngineCore::AssetManager* temp = EngineCore::AssetManager::GetInstance();
    int check = -1;

    check -= temp->CacheSprite("sprPlayer");
    check -= temp->CacheSprite("sprEnemy");
    check -= temp->CacheSprite("sprTrishotEnemy");
    check -= temp->CacheSprite("sprBurstEnemy");
    check -= temp->CacheMusic("bgm01", "ogg");

    return check != 0;
}
