#include "EnemyBullet.h"
#include "IDamagable.h"
#include "ObjectHandler.h"
#include "Player.h"
#include <cmath>
#include <iostream>

EnemyBullet::EnemyBullet(float x, float y, SDL_Color bulletColor, float speed, float direction, float width, float height): GameObject(x, y, Tag::ObjectEnemyBullet), Object(Tag::ObjectEnemyBullet)
{
    set_speed(speed);
    set_direction(direction);
    set_width(width);
    set_height(height);
    this->bulletColor = bulletColor;
    radius = width/2;
}

void EnemyBullet::start()
{

}

void EnemyBullet::tick(){
    move();

    destroy_outside();
}

void EnemyBullet::draw_bounds(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int w = 0; w < (radius * 2) + 1; w++)
    {
        for (int h = 0; h < (radius * 2) + 1; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            float size = (dx * dx + dy * dy);
            if (size >= (radius * radius) && size <= ((radius + 1) * (radius + 1))){
                SDL_RenderDrawPoint(renderer, get_center_x() + dx, get_center_y() + dy);
            }
        }
    }
}

void EnemyBullet::render(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, bulletColor.r, bulletColor.g, bulletColor.b, 255);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, get_center_x() + dx, get_center_y() + dy);
            }
        }
    }
}

void EnemyBullet::collision(GameObject* other){
    if (other->get_tag() == Tag::ObjectPlayer){
        if (dynamic_cast<IDamagable*>(other)){
            destroy();
        }
    }
}
