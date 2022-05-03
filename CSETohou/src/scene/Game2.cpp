#include "Game2.h"
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

using UI::UILabel;

Game2::Game2()
{
    
}

void Game2::Tick() {
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

    //volumeLabel->SetText("Volume:" + std::to_string(volume));
}

void Game2::Render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 79, 0, 129, 128);
    SDL_RenderFillRectF(renderer, &left);
    SDL_RenderFillRectF(renderer, &right);
    SDL_RenderFillRectF(renderer, &up);
    SDL_RenderFillRectF(renderer, &down);
}

bool Game2::Start() {
    EngineCore::ObjectHandler* oHandler = EngineCore::ObjectHandler::GetInstance();
    Mix_Music* music = EngineCore::AssetManager::GetInstance()->GetCachedMusic("bgm02");

    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(music, -1);
        Mix_VolumeMusic(volume);

        std::cout << "Game2: start()\n";
        oHandler->Instantiate(new Player(GAME_WIDTH / 2, GAME_HEIGHT - GRID_SIZE * 2));
        oHandler->Instantiate(new EnemySpawner());
        //volumeLabel = dynamic_cast<UILabel*>(oHandler->Instantiate(new UILabel(MAX_X+GRID_SIZE*2, GRID_SIZE*8, 128, 32, "Volume")));

    }
    return true;
}

bool Game2::LoadSceneAssets()
{
    EngineCore::AssetManager* temp = EngineCore::AssetManager::GetInstance();
    int check = -1;

    check -= temp->CacheSprite("sprPlayer");
    check -= temp->CacheSprite("sprEnemy");
    check -= temp->CacheSprite("sprTrishotEnemy");
    check -= temp->CacheSprite("sprBurstEnemy");
    check -= temp->CacheMusic("bgm02", "ogg");

    return check != 0;
}
