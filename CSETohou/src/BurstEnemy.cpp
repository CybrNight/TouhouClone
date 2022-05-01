#include "BurstEnemy.h"
#include "ObjectHandler.h"
#include "Enemybullet.h"
#include <cmath>
#include <iostream>

BurstEnemy::BurstEnemy(float x, float y, float direction) : Enemy(x, y), GameObject(x, y, Tag::ObjectEnemy), Object(Tag::ObjectEnemy)
{
    width = 24;
    height = 24;
    startY = y;
    SetDirection(direction);
    bulletColor = SDL_Color{0, 255, 255};
    sprName = "sprBurstEnemy";
}

void BurstEnemy::Start(){
    speed = 3;
    rotation = 0;
    health = 1;
    shootTimer = 0;
    fireRate = 1;
    counter = 0;
}

void BurstEnemy::Collision(GameObject* other){
   
}

void BurstEnemy::Tick(){
    //Rotate and move every frame
    rotation += 5;
    Move();

    //Switch to attack mode after getting on screen
    if (enemyState == EnemyState::Warmup){
        if (GetY() >= startY + GRID_SIZE * 2) {
            SetEnemyState(EnemyState::Attack);
        }
    }

    if (enemyState == EnemyState::Attack){
        counter ++;

        if (counter >= Time::SECOND){
            if (Player::GetPlayer() == NULL)
                return;

            distX = Player::GetPlayer()->GetX()-GetX();
            distY = -(Player::GetPlayer()->GetY()-GetY());

            angle = std::atan2(distY, distX) * 180/M_PI;

            for (int i = 0; i < 180; i+=10){
                 float x = std::cos(i * M_PI/180) * width/2;
                 float y = std::sin(i * M_PI/180) * height/2;
                 Instantiate(new EnemyBullet(GetX() + x, GetY() + y, SDL_Color{0, 255, 255}, std::rand() % 10 + 5, angle));
            }
            Destroy();
        }

        if (health <= 0) {
            Destroy();
            
            for (int i = 0; i < 360; i += 20) {
                Instantiate(new EnemyBullet(GetCenterX(), GetCenterY(), SDL_Color{0, 255, 255}, 4, i));
            }
        }
    }

}
