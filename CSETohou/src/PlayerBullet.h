#pragma once

#include "gameobject.h"
#include <string>

class PlayerBullet : public virtual GameObject
{
    float velX = 0, velY = 0;
    SDL_Color color{255, 0, 255};
    std::string strPath = "";

protected:
    //Called every frame
    void Start();
    void Tick();

public:
    PlayerBullet(float x, float y, SDL_Color color);
    //Bullet(float x, float y, ID id = ID::ObjectBullet, std::string strPath = ":/sprites/sprBullet");
    ~PlayerBullet(){}

    //Called when other Collider overlaps
    void Collision(GameObject* other);
    void Render(SDL_Renderer* painter);
};