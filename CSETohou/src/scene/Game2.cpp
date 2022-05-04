#include "Game2.h"
#include "ObjectHandler.h"
#include "Player.h"
#include "Defs.h"
#include <iostream>
#include "BasicEnemy.h"
#include "EnemySpawner.h"
#include "BurstEnemy.h"
#include "SceneManager.h"
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using CybrEngine::SceneManager;
using CybrEngine::Input;
using CybrEngine::AssetManager;

using UI::UILabel;

Game2::Game2()
{
    drawRect = {0,0,1280, 1024};
    boundsRect = {0,0,GAME_WIDTH, GAME_HEIGHT};
}

void Game2::Tick() {
    Input* input = Input::GetInstance();

    if (input->GetKeyDown(SDL_SCANCODE_RETURN)) {
        SceneManager::LoadScene("Game");
    }

    //volumeLabel->SetText("Volume:" + std::to_string(volume));
}

void Game2::Render(SDL_Renderer* renderer) {
    //SDL_RenderCopy(renderer, background.get(), &drawRect, &boundsRect);
    SDL_SetRenderDrawColor(renderer, 79, 0, 129, 128);
    SDL_RenderFillRectF(renderer, &left);
    SDL_RenderFillRectF(renderer, &right);
    SDL_RenderFillRectF(renderer, &up);
    SDL_RenderFillRectF(renderer, &down);
   
}

bool Game2::Start() {
    CybrEngine::ObjectHandler* oHandler = CybrEngine::ObjectHandler::GetInstance();

    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(AssetManager::GetInstance()->GetCachedMusic("bgm02").get(), -1);
        Mix_VolumeMusic(volume);

        std::cout << "Game2: start()\n";
        volumeLabel = std::dynamic_pointer_cast<UILabel>(oHandler->Instantiate(new UILabel(GAME_WIDTH/2 - 64, GAME_HEIGHT / 2 - 16, 128, 32, "GLORIUS GAME!")));
        background = AssetManager::GetInstance()->GetCachedSprite("backgroundSpace");
    }
    return true;
}

bool Game2::LoadSceneAssets()
{
    AssetManager* temp = AssetManager::GetInstance();
    int check = -1;

    check -= temp->CacheSprite("sprPlayer");
    check -= temp->CacheSprite("sprEnemy");
    check -= temp->CacheSprite("sprTrishotEnemy");
    check -= temp->CacheSprite("sprBurstEnemy");
    check -= temp->CacheMusic("bgm02", "ogg");
    check -= temp->CacheSprite("backgroundSpace");

    return check != 0;
}
