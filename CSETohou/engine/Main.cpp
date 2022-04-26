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

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
std::shared_ptr<SDL_Renderer> renderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

Game* game;
Handler* handler;
AssetManager* aManager;

Mix_Music* music = NULL;

Mix_Chunk* gScratch = NULL;
Mix_Chunk* gHigh = NULL;
Mix_Chunk* gMedium = NULL;
Mix_Chunk* gLow = NULL;

bool init()
{
    //Initialization flag
    bool success = true;
    //Initialize SDL

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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

void close()
{
    //Free loaded image
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    //Destroy window	
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    renderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void tick() {
    handler->tick();
    game->tick();
}

void input(SDL_KeyboardEvent& e) {
    handler->input(e);
}

void render() {
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(renderer.get());

    handler->render();
    game->render();
    //Clear screen


    //Update screen
    SDL_RenderPresent(renderer.get());
}

int main(int argc, char* args[])
{
    //Start up SDL and create window
    if (!init())
    {
        printf("Main: Failed to initialize!\n");
    }
    else
    {
        //Main loop flag
        bool quit = false;
        //Event handler
        SDL_Event e;

        game = new Game(renderer);
        handler = new Handler(renderer);
        aManager = new AssetManager(renderer);

        game->start();

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


                if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
                    input(e.key);
                }

            }

            Uint64 start = SDL_GetPerformanceCounter();

            tick();
            render();


            Uint64 end = SDL_GetPerformanceCounter();

            float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
            //Cap to 60FPS
            SDL_Delay(floor(16.666f - elapsedMS));
            Time::DELTA_TIME = floor(16.666f - elapsedMS) / 1000;
            Time::SECOND = Time::FRAMERATE;
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}