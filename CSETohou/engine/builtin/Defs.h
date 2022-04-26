#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;
constexpr int GRID_SIZE = 32;
constexpr int MIN_X = GRID_SIZE;
constexpr int MIN_Y = GRID_SIZE / 2;
constexpr int MAX_X = GRID_SIZE * 13;
constexpr int MAX_Y = SCREEN_HEIGHT - GRID_SIZE / 2;
constexpr int GAME_WIDTH = MAX_X - MIN_X;
constexpr int GAME_HEIGHT = MAX_Y - MIN_Y;
constexpr int VERT_CENTER = MIN_X + (GAME_WIDTH / 2);
constexpr int HORZ_CENTER = MIN_Y + (GAME_HEIGHT / 2);

struct Time {
	static constexpr int FRAMERATE = 60;
	static float DELTA_TIME;
	static float SECOND;

};

struct TextureDeleter
{
	void operator()(SDL_Texture* tp) {
		SDL_DestroyTexture(tp);
	}
};

inline float clamp(float value, float min, float max) {
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

struct sdl_deleter
{
	void operator()(SDL_Window* p) const { SDL_DestroyWindow(p); }
	void operator()(SDL_Renderer* p) const { SDL_DestroyRenderer(p); }
	void operator()(SDL_Texture* p) const { SDL_DestroyTexture(p); }
};