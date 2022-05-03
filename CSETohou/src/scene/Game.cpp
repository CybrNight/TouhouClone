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

using CybrEngine::Input;

float Time::DELTA_TIME;
float Time::SECOND;

using UI::UILabel;

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

void Game::Render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 79, 0, 129, 128);
    SDL_RenderFillRectF(renderer, &left);
    SDL_RenderFillRectF(renderer, &right);
    SDL_RenderFillRectF(renderer, &up);
    SDL_RenderFillRectF(renderer, &down);
}

bool Game::Start() {
    CybrEngine::ObjectHandler* oHandler = CybrEngine::ObjectHandler::GetInstance();
    music = CybrEngine::AssetManager::GetInstance()->GetCachedMusic("bgm01");

    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(music, -1);
        Mix_VolumeMusic(volume);

        std::cout << "Game: start()\n";
        oHandler->Instantiate(new Player(GAME_WIDTH / 2, GAME_HEIGHT - GRID_SIZE * 2));
        oHandler->Instantiate(new EnemySpawner());
        volumeLabel = std::dynamic_pointer_cast<UILabel>(oHandler->Instantiate(new UILabel(MAX_X+GRID_SIZE*2, GRID_SIZE*8, 128, 32, "Volume")));

    }
    return true;
}

bool Game::LoadSceneAssets()
{
    CybrEngine::AssetManager* temp = CybrEngine::AssetManager::GetInstance();
    int check = -1;

    check -= temp->CacheSprite("sprPlayer");
    check -= temp->CacheSprite("sprEnemy");
    check -= temp->CacheSprite("sprTrishotEnemy");
    check -= temp->CacheSprite("sprBurstEnemy");
    check -= temp->CacheMusic("bgm01", "ogg");

    return check != 0;
}
