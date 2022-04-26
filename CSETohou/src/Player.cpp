#include "Player.h"
#include "ObjectHandler.h"
#include "PlayerBullet.h"
Player* Player::instance;
#include <iostream>

Player::Player(float x, float y, Tag tag): GameObject(x, y, tag), Object(tag) {
    width = 32;
    height = 32;

    bulletColor = SDL_Color{255, 0, 255};

    instance = this;
    this->sprName = "sprPlayer";
    std::cout << (int)this->get_tag();
}

void Player::draw_bounds(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, bulletColor.r, bulletColor.g, bulletColor.b, 255);
    for (int w = 0; w < 8; w++)
    {
        for (int h = 0; h < 8; h++)
        {
            int dx = 4 - w; // horizontal offset
            int dy = 4 - h; // vertical offset
            if ((dx * dx + dy * dy) <= (4 * 4))
            {
                SDL_RenderDrawPoint(renderer, get_center_x() + dx, get_center_y() + dy);
            }
        }
    }
}

SDL_FRect Player::get_bounds() const
{
    return SDL_FRect{ get_center_x() - 4, get_center_y() - 4, 8, 8 };
}


void Player::start(){
    velX = 0;
    velY = 0;
    speed = 5;
    rotation = 0;
}

void Player::tick(){
    //objectSize = QRectF(get_center_x()-4, get_center_y()-4, 8, 8);

    x += velX;
    y += velY;

    clamp_position();

    shootTimer ++;

    if (shoot && shootTimer >= Time::SECOND/fireRate){
        instantiate(new PlayerBullet(get_center_x()-width/2, get_center_y()-height/6, bulletColor));
        instantiate(new PlayerBullet(get_center_x()+width/3, get_center_y()-height/6, bulletColor));

        shootTimer = 0;
    }

}

void Player::collision(GameObject* other){
    /*if (other->get_tag() == Tag::ObjectEnemyBullet){
        destroy();
        this->instance = NULL;
        Handler::instance->remove_with_tag(Tag::ObjectEnemy);
        Handler::instance->remove_with_tag(Tag::ObjectEnemyBullet);

        instantiate(new Player(GAME_WIDTH/2, MAX_Y - GRID_SIZE*2));
    }*/
}

void Player::damage()
{
    std::cout << "Player: damage()\n";
}

void Player::key_press(SDL_Keycode key){
    if (key == SDLK_LEFT) {
        keysDown[0] = true;
        velX = -speed;
    }
    if (key == SDLK_RIGHT) {
        keysDown[1] = true;
        velX = speed;
    }
    if (key == SDLK_UP) {
        keysDown[2] = true;
        velY = -speed;
    }
    if (key == SDLK_DOWN) {
        velY = speed;
        keysDown[3] = true;
    }


    if (key == SDLK_z) {
        shoot = true;
    }

    if (key == SDLK_LSHIFT) {
        speed = 2;
    }
}

void Player::key_release(SDL_Keycode key){
    switch (key) {
        case SDLK_LEFT:
            keysDown[0] = false;
            break;
        case SDLK_RIGHT:
            keysDown[1] = false;
            break;
        case SDLK_UP:
            keysDown[2] = false;
            break;
        case SDLK_DOWN:
            keysDown[3] = false;
            break;

    }

    if (!keysDown[0] && !keysDown[1]) velX = 0;
    if (!keysDown[2] && !keysDown[3]) velY = 0;

    if (key == SDLK_z) {
        shoot = false;
    }

    if (key == SDLK_LSHIFT){
        speed = 5;
    }
}

void Player::key_held(SDL_Keycode key){
    if (key == SDLK_LEFT){
        keysDown[0] = true;
        velX = -speed;
    }
    if (key == SDLK_RIGHT){
        keysDown[1] = true;
        velX = speed;
    }
    if (key == SDLK_UP){
        keysDown[2] = true;
        velY = -speed;
    }
    if (key == SDLK_DOWN){
        velY = speed;
        keysDown[3] = true;
    }


    if (key == SDLK_z){
        shoot = true;
    }

    if (key == SDLK_LSHIFT){
        speed = 2;
    }
}

/*void Player::damage(){
    destroy();
}*/
