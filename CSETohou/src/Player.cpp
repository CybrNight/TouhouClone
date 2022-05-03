#include "Player.h"
#include "ObjectHandler.h"
#include "PlayerBullet.h"
#include "Input.h"
#include "SceneManager.h"
#include "Game.h"
#include <iostream>

Player* Player::instance;

Player::Player(float x, float y, Tag tag): GameObject(x, y, tag), Object(tag) {
    width = 32;
    height = 32;

    bulletColor = SDL_Color{255, 0, 255};

    this->sprName = "sprPlayer";
    std::cout << (int)this->GetTag();
    instance = this;
}

void Player::DrawBounds(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, bulletColor.r, bulletColor.g, bulletColor.b, 255);
    for (int w = 0; w < 8; w++)
    {
        for (int h = 0; h < 8; h++)
        {
            int dx = 4 - w; // horizontal offset
            int dy = 4 - h; // vertical offset
            if ((dx * dx + dy * dy) <= (4 * 4))
            {
                SDL_RenderDrawPoint(renderer, GetCenterX() + dx, GetCenterY() + dy);
            }
        }
    }
}

SDL_FRect Player::GetBounds() const
{
    return SDL_FRect{ GetCenterX() - 4, GetCenterY() - 4, 8, 8 };
}


void Player::Start(){
    velX = 0;
    velY = 0;
    speed = 5;
    rotation = 0;
}

void Player::Tick(){
    CybrEngine::Input& input = *(CybrEngine::Input::GetInstance());

    if (input.GetKey(SDL_SCANCODE_LEFT)) {
        velX = -speed;
        keysDown[0] = true;
    }
    if (input.GetKey(SDL_SCANCODE_RIGHT)) {
        velX = speed;
        keysDown[1] = true;
    }
    if (input.GetKey(SDL_SCANCODE_UP)) {
        velY = -speed;
        keysDown[2] = true;
    }
    if (input.GetKey(SDL_SCANCODE_DOWN)) {
        velY = speed;
        keysDown[3] = true;
    }

    if (input.GetKeyUp(SDL_SCANCODE_LEFT)) {
        keysDown[0] = false;
    }
    if (input.GetKeyUp(SDL_SCANCODE_RIGHT)) {
        keysDown[1] = false;
    }
    if (input.GetKeyUp(SDL_SCANCODE_UP)) {
        keysDown[2] = false;
    }
    if (input.GetKeyUp(SDL_SCANCODE_DOWN)) {
        keysDown[3] = false;
    }

    if (input.GetKey(SDL_SCANCODE_Z)) {
        shoot = true;
    }

    if (input.GetKeyUp(SDL_SCANCODE_Z)) {
        shoot = false;
    }

    if (input.GetKeyDown(SDL_SCANCODE_LSHIFT)) {
        speed = 2.5f;
    }
    
    if (input.GetKeyUp(SDL_SCANCODE_LSHIFT)) {
        speed = 5;
    }

    if (keysDown[0] == false && keysDown[1] == false) velX = 0;
    if (keysDown[2] == false && keysDown[3] == false) velY = 0;

    x += velX;
    y += velY;

    ClampPosition();

    shootTimer ++;

    if (shoot && shootTimer >= Time::SECOND/fireRate){
        Instantiate(new PlayerBullet(GetCenterX()-width/2, GetCenterY()-height/6, bulletColor));
        Instantiate(new PlayerBullet(GetCenterX()+width/3, GetCenterY()-height/6, bulletColor));

        shootTimer = 0;
    }

}

void Player::Collision(GameObject* other){
    if (other->GetTag() == Tag::ObjectEnemyBullet){
        //Destroy();
    }
}

void Player::Damage()
{
    std::cout << "Player: damage()\n";
}

/*void Player::Damage(){
    destroy();
}*/
