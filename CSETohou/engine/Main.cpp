/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Game.h"
#include "ObjectHandler.h"
#include <iostream>
#include <SDL_mixer.h>
#include "AssetManager.h"
#include "Input.h"


//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
std::shared_ptr<SDL_Renderer> renderer = NULL;

Game* game;
EngineCore::ObjectHandler* handler;
EngineCore::AssetManager* aManager;
EngineCore::Input* input;

bool Init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVERYTHING) < 0)
    {
        printf("Main: SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Main: Warning: Linear texture filtering not enabled!");
        }

        //Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Main: Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Create renderer for window
            renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);
            if (renderer == NULL)
            {
                printf("Main: Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor(renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);

                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                    printf("Main: SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

void Close()
{
    //Destroy window	
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    renderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void Tick() {
    handler->Tick();
    game->Tick();
}

void Input(SDL_Event& e) {
    input->InputEvent(e);
}

void Render() {
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(renderer.get());

    handler->Render();
    game->Render();
    //Clear screen


    //Update screen
    SDL_RenderPresent(renderer.get());
}

int main(int argc, char* args[]) {
    //Start up SDL and create window
    if (!Init()) {
        printf("Main: Failed to initialize!\n");
    }
    else {
        //Main loop flag
        bool quit = false;
        //Event handler
        SDL_Event e;

        //Get reference to singletons
        game = Game::GetInstance(renderer);
        handler = EngineCore::ObjectHandler::GetInstance(renderer);
        aManager = EngineCore::AssetManager::GetInstance (renderer);
        input = EngineCore::Input::GetInstance();

        if (game->Start()) {
            //While application is running
            while (!quit)
            {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0)
                {
                    //User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }

                    Input(e);

                }

                Uint64 start = SDL_GetPerformanceCounter();

                Tick();
                Render();


                Uint64 end = SDL_GetPerformanceCounter();

                float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
                //Cap to 60FPS
                SDL_Delay(floor(16.666f - elapsedMS));
                Time::DELTA_TIME = floor(16.666f - elapsedMS) / 1000;
                Time::SECOND = Time::FRAMERATE;
            }
        }
        else {
            std::cout << "Main: Failed to start Game\n";
        }


        //Free resources and close SDL
        Close();

        return 0;
    }
}