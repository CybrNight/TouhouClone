#pragma once

#include "GameObject.h"
#include "Game.h"
#include <iostream>

class EnemyBullet : public GameObject
{
    float direction = 0;
    float speed = 0;
    float radius = 0;
    SDL_Color bulletColor{255, 0, 0};

protected:
    void Start();
    void Tick();
    void Render(SDL_Renderer* renderer);

public:
    EnemyBullet(float x, float y, SDL_Color bulletColor, float speed = 600, float direction = 270, float width = GRID_SIZE/4, float height = GRID_SIZE/2);
    ~EnemyBullet() { }

    void Collision(GameObject* other);
};
