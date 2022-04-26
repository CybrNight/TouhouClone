#include "BasicEnemy.h"
#include "ObjectHandler.h"
#include "EnemyBullet.h"
#include "Player.h"

BasicEnemy::BasicEnemy(float x, float y, float direction): Enemy(x, y), GameObject(x, y, Tag::ObjectEnemy), Object(Tag::ObjectEnemy)
{
    width = 26;
    height = 26;
    set_direction(direction);
    distance = y + (std::rand() % 2 + 1) * GRID_SIZE*0.8125f;
    bulletColor = SDL_Color{0, 255, 0};
    sprName = "sprEnemy";
}

void BasicEnemy::start(){
    fireRate = 2;
    health = 5;
    speed = 0;
    rotation = 180;
    counter = 0;
}

//Here is an example of how to use a counter variable to write an AI pattern
void BasicEnemy::tick(){
    if (enemyState == EnemyState::Warmup){
        GameObject::move();
        if (get_y() < distance && counter == 0) {
            speed = 5;
            this->set_direction(270);
        }else{
            set_enemy_state(EnemyState::Attack);
        }
    }

    if (enemyState == EnemyState::Attack){
        move();
        counter += Time::DELTA_TIME;
        shootTimer += Time::DELTA_TIME;

        speed = 1;
        canShoot = true;


        if (shootTimer >= Time::SECOND/fireRate && canShoot){
            if (Player::get_player() == NULL)
                return;

            distX = Player::get_player()->get_x()-get_x();
            distY = -(Player::get_player()->get_y()-get_y());

            angle = std::atan2(distY, distX) * 180/M_PI;

            instantiate(new EnemyBullet(get_x(), get_y(), bulletColor, 5, angle, GRID_SIZE * 0.80));
            shootTimer = 0;
        }

        if (health < 1){
            destroy();
        }
    }

    if (enemyState == EnemyState::Retreat){
        GameObject::move();
        direction = 90;
        speed = 12;

        destroy_outside();
    }

    clamp_x();
}

void BasicEnemy::collision(GameObject* other){

}

void BasicEnemy::move()
{
    float c = std::cos(180 * M_PI/180);
    float s = std::sin(180 * M_PI/180);
    

    float wobble = amplitude * std::sin(frequency * counter) * frequency * Time::DELTA_TIME;

    //std::cout << (c * speed * Time::DELTA_TIME) - (s * wobble) << '\n';
    y -= (c * speed * Time::DELTA_TIME) - (s * wobble);
    x += (s * speed * Time::DELTA_TIME) - (c * wobble);
}
