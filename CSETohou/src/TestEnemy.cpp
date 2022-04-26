#include "TestEnemy.h"
#include "ObjectHandler.h"
#include "EnemyBullet.h"
#include "Player.h"

//USE ME FOR TESTING NEW ENEMY IDEAS!!! DUPLICATE AND REFACTOR WHEN DONE!!!
TestEnemy::TestEnemy(float x, float y, float direction) : Enemy(x, y), GameObject(x, y, Tag::ObjectEnemy), Object(Tag::ObjectEnemy)
{
    set_direction(direction);
    distance = MIN_Y + (std::rand() % 4 + 1) * GRID_SIZE*0.8125f;
    bulletColor = {255, 255, 0};
}

void TestEnemy::start(){
    fireRate = 10;
    health = 5;
    speed = 3;
    rotation = 180;
    counter = 0;
}

//Here is an example of how to use a counter variable to write an AI pattern
void TestEnemy::tick(){
    if (enemyState == EnemyState::Warmup){
        GameObject::move();
        if (y < distance && counter == 0){
            speed = 5;
            //this->set_direction(270);
        }else{
            set_enemy_state(EnemyState::Attack);
        }
    }

    if (enemyState == EnemyState::Attack){
        move();
        counter ++;
        shootTimer ++;

        speed = 0;
        canShoot = true;
        float width = 8;


        if (shootTimer >= 60/fireRate && canShoot){
            instantiate(new EnemyBullet(x, y, bulletColor, 200, -135, width));
            instantiate(new EnemyBullet(x, y, bulletColor, 200, -90, width));
            instantiate(new EnemyBullet(x, y, bulletColor, 200, -45, width));
                    
            instantiate(new EnemyBullet(x, y, bulletColor, 200, -30, width));
            instantiate(new EnemyBullet(x, y, bulletColor, 200, -60, width));
       
            instantiate(new EnemyBullet(x, y, bulletColor, 200, -120, width));
            instantiate(new EnemyBullet(x, y, bulletColor, 200, -150, width));


            shootTimer = 0;
        }
    }

    if (enemyState == EnemyState::Retreat){
        GameObject::move();
        direction = 90;
        speed = 10;

        destroy_outside();
    }

    clamp_x();
}

void TestEnemy::collision(GameObject* other){
    if (other->get_tag() == Tag::ObjectPlayerBullet){
        health --;

        if (health == 0){
            for (int i = 0; i < 360; i += 10){
                instantiate(new EnemyBullet(x, y, bulletColor, 5, i));
            }
            destroy();
        }
    }
}

void TestEnemy::move()
{
    float c = std::cos(direction * M_PI/180);
    float s = std::sin(direction * M_PI/180);

    float wobble = amplitude * std::sin(frequency * counter) * frequency;

    x += (c * speed) - s * wobble ;
    y -= (s * speed) + c * wobble ;
}
