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
#include "Input.h"
#include <SDL_ttf.h>

using EngineCore::Input;

float Time::DELTA_TIME;
float Time::SECOND;

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

    //this opens a font style and sets a size
    TTF_Font* Sans = TTF_OpenFont("resource/font/test.ttf", 24);

    // this is the color in rgb format,
    // maxing out all would give you the color white,
    // and it will be your text's color
    SDL_Color White = { 255, 255, 255 };

    // as TTF_RenderText_Solid could only be used on
    // SDL_Surface then you have to create the surface first
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, ("Volume:" + std::to_string(volume)).c_str(), White);

    // now you can convert it into a texture
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer.get(), surfaceMessage);

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate 
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = 100; // controls the width of the rect
    Message_rect.h = 24; // controls the height of the rect

    // (0,0) is on the top left of the window/screen,
    // think a rect as the text's box,
    // that way it would be very simple to understand

    // Now since it's a texture, you have to put RenderCopy
    // in your game loop area, the area where the whole code executes

    // you put the renderer's name first, the Message,
    // the crop size (you can ignore this if you don't want
    // to dabble with cropping), and the rect which is the size
    // and coordinate of your texture
    SDL_RenderCopy(renderer.get(), Message, NULL, &Message_rect);
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
