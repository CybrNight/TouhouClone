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

Game::Game(std::shared_ptr<SDL_Renderer> renderer)
{
    this->renderer = renderer;
}

void Game::tick() {
    
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer.get(), 79, 0, 129, 128);
    SDL_RenderFillRectF(renderer.get(), new SDL_FRect{ 0, 0, MIN_X, SCREEN_HEIGHT });
    SDL_RenderFillRectF(renderer.get(), new SDL_FRect{ 0, MAX_Y, SCREEN_WIDTH, SCREEN_HEIGHT });
    SDL_RenderFillRectF(renderer.get(), new SDL_FRect{ 0, 0, SCREEN_WIDTH, MIN_Y });
    SDL_RenderFillRectF(renderer.get(), new SDL_FRect{ MAX_X, 0, SCREEN_WIDTH, SCREEN_HEIGHT });

}


void Game::start() {
    Mix_Music* music = AssetManager::getAssetManager()->getMusic("bgm01");

    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(music, -1);

        std::cout << "Game: start()\n";
        instantiate(new Player(GAME_WIDTH / 2, GAME_HEIGHT - GRID_SIZE * 2));
        instantiate(new EnemySpawner());
    }
}