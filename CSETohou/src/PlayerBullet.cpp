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

void PlayerBullet::Start()
{
    speed = 15;
    SetDirection(90);
}

void PlayerBullet::Tick(){
    Move();

    DestroyOutside();
}

void PlayerBullet::Collision(GameObject* other){
    if (other->GetTag() == Tag::ObjectEnemy){
        if (auto Damage = dynamic_cast<IDamagable*>(other)){
            Damage->Damage();
        }

        Destroy();
    }
}

void PlayerBullet::Render(SDL_Renderer* renderer)
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
                SDL_RenderDrawPoint(renderer, GetCenterX() + dx, GetCenterY() + dy);
            }
        }
    }
}
