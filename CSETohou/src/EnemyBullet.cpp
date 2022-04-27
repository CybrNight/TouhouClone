#include "EnemyBullet.h"
#include "IDamagable.h"
#include "ObjectHandler.h"
#include "Player.h"
#include <cmath>
#include <iostream>

EnemyBullet::EnemyBullet(float x, float y, SDL_Color bulletColor, float speed, float direction, float width, float height): GameObject(x, y, Tag::ObjectEnemyBullet), Object(Tag::ObjectEnemyBullet)
{
    SetSpeed(speed);
    SetDirection(direction);
    SetWidth(width);
    SetHeight(height);
    this->bulletColor = bulletColor;
    radius = width/2;
}

void EnemyBullet::Start()
{

}

void EnemyBullet::Tick(){
    Move();

    DestroyOutside();
}

void EnemyBullet::Render(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, bulletColor.r, bulletColor.g, bulletColor.b, 255);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, GetCenterX() + dx, GetCenterY() + dy);
            }
        }
    }
}

void EnemyBullet::Collision(GameObject* other){
    if (other->GetTag() == Tag::ObjectPlayer){
        if (dynamic_cast<IDamagable*>(other)){
            Destroy();
        }
    }
}
