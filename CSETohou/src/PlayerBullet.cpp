#include "PlayerBullet.h"
#include "ObjectHandler.h"
#include "Enemy.h"
#include "Game.h"
#include "IDamagable.h"


PlayerBullet::PlayerBullet(float x, float y, SDL_Color color): GameObject(x, y, Tag::ObjectPlayerBullet), Object(Tag::ObjectPlayerBullet)
{
    width = height = GRID_SIZE/4;
    this->color = color;

}

void PlayerBullet::draw_bounds(SDL_Renderer* renderer) {
    float radius = width/2;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int w = 0; w < (radius * 2) + 1; w++)
    {
        for (int h = 0; h < (radius * 2) + 1; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            float size = (dx * dx + dy * dy);
            if (size >= (radius * radius) && size <= ((radius + 1) * (radius + 1))) {
                SDL_RenderDrawPoint(renderer, get_center_x() + dx, get_center_y() + dy);
            }
        }
    }
}

void PlayerBullet::start()
{
    speed = 15;
    set_direction(90);
}

void PlayerBullet::tick(){
    move();

    destroy_outside();
}

void PlayerBullet::collision(GameObject* other){
    if (other->get_tag() == Tag::ObjectEnemy){
        if (auto damage = dynamic_cast<IDamagable*>(other)){
            damage->damage();
        }

        destroy();
    }
}

void PlayerBullet::render(SDL_Renderer* renderer)
{
    SDL_Color bulletColor{255, 0, 255};
    SDL_SetRenderDrawColor(renderer, bulletColor.r, bulletColor.g, bulletColor.b, 255);
    float radius = width / 2;
    for (int w = 0; w < (radius * 2) + 1; w++)
    {
        for (int h = 0; h < (radius * 2) + 1; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            float size = (dx * dx + dy * dy);
            if (size <= ((radius) * (radius))) {
                SDL_RenderDrawPoint(renderer, get_center_x() + dx, get_center_y() + dy);
            }
        }
    }
}
