#pragma once

#include <gameobject.h>
#include "game.h"

class EnemyBullet : public GameObject
{
    float direction = 0;
    float speed = 0;
    float radius = 0;
    SDL_Color bulletColor{255, 0, 0};

protected:
    void start();
    void tick();
    void render(SDL_Renderer* renderer);
    void draw_bounds(SDL_Renderer* renderer);

public:
    EnemyBullet(float x, float y, SDL_Color bulletColor, float speed = 600, float direction = 270, float width = GRID_SIZE/4, float height = GRID_SIZE/2);
    ~EnemyBullet(){}

    void collision(GameObject* other);
};
