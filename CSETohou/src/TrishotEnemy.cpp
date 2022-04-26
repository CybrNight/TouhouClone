#include "TrishotEnemy.h"
#include "ObjectHandler.h"
#include "EnemyBullet.h"
#include "Player.h"

//USE ME FOR TrishotING NEW ENEMY IDEAS!!! DUPLICATE AND REFACTOR WHEN DONE!!!
TrishotEnemy::TrishotEnemy(float x, float y, float direction) : Enemy(x, y), GameObject(x, y, Tag::ObjectEnemy), Object(Tag::ObjectEnemy)
{
    width = 32;
    height = 32;
    set_direction(direction);
    distance = MIN_Y + (std::rand() % 4 + 1) * GRID_SIZE*0.8125f;

    sprName = "sprTrishotEnemy";
}

void TrishotEnemy::start(){
    fireRate = 10;
    health = 10;
    speed = 3;
    rotation = 180;
    counter = 0;
}

//Here is an example of how to use a counter variable to write an AI pattern
void TrishotEnemy::tick(){
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

        speed = 1;
        canShoot = true;
        float width = 8;


        if (shootTimer >= 60/fireRate && canShoot){
            instantiate(new EnemyBullet(get_center_x(), y+height, bulletColor, 5, -135, width));
            instantiate(new EnemyBullet(get_center_x(), y+height, bulletColor, 5, -90, width));
            instantiate(new EnemyBullet(get_center_x(), y+height, bulletColor, 5, -45, width));

            instantiate(new EnemyBullet(get_center_x(), y+height, bulletColor, 5, -30, width));
            instantiate(new EnemyBullet(get_center_x(), y+height, bulletColor, 5, -60, width));

            instantiate(new EnemyBullet(get_center_x(), y+height, bulletColor, 5, -120, width));
            instantiate(new EnemyBullet(get_center_x(), y+height, bulletColor, 5, -150, width));


            shootTimer = 0;
        }


        if (health == 0){
            destroy();
        }
    }

    if (enemyState == EnemyState::Retreat){
        GameObject::move();
        direction = 90;
        speed = 8;

        destroy_outside();
    }

    clamp_x();
}

void TrishotEnemy::move()
{
    float c = std::cos(180 * M_PI / 180);
    float s = std::sin(180 * M_PI / 180);


    float wobble = amplitude * std::sin(frequency * counter) * frequency * Time::DELTA_TIME;

    //std::cout << (c * speed * Time::DELTA_TIME) - (s * wobble) << '\n';
    y -= (c * speed * Time::DELTA_TIME) - (s * wobble);
    x += (s * speed * Time::DELTA_TIME) - (c * wobble);
}
