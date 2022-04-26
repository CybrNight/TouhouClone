#include "BurstEnemy.h"
#include "ObjectHandler.h"
#include "Enemybullet.h"
#include <cmath>

BurstEnemy::BurstEnemy(float x, float y, float direction) : Enemy(x, y), GameObject(x, y, Tag::ObjectEnemy), Object(Tag::ObjectEnemy)
{
    width = 24;
    height = 24;
    startY = y;
    set_direction(direction);
    bulletColor = SDL_Color{0, 255, 255};
    sprName = "sprBurstEnemy";
}

void BurstEnemy::start(){
    speed = 5;
    rotation = 0;
    health = 1;
    shootTimer = 0;
    fireRate = 1;
    counter = 0;
}

void BurstEnemy::collision(GameObject* other){
    if (other->get_tag() == Tag::ObjectPlayerBullet){
        ::destroy(other);
    }
}

void BurstEnemy::tick(){
    rotation += 5;
    move();

    if (enemyState == EnemyState::Warmup){
        if (get_y() >= startY + GRID_SIZE * 4) {
            speed = 0;
            set_enemy_state(EnemyState::Attack);
        }
    }

    if (enemyState == EnemyState::Attack){
        counter ++;

        if (counter >= Time::SECOND){
            if (Player::get_player() == NULL)
                return;

            distX = Player::get_player()->get_x()-get_x();
            distY = -(Player::get_player()->get_y()-get_y());

            angle = std::atan2(distY, distX) * 180/M_PI;

            for (int i = 0; i < 180; i+=10){
                 float x = std::cos(i * M_PI/180) * width/2;
                 float y = std::sin(i * M_PI/180) * height/2;
                 instantiate(new EnemyBullet(get_x() + x, get_y() + y, SDL_Color{0, 255, 255}, std::rand() % 10 + 5, angle));
            }
            destroy();
        }
    }

}
