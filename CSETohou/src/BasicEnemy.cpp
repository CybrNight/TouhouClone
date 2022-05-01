#include "BasicEnemy.h"
#include "ObjectHandler.h"
#include "EnemyBullet.h"
#include "Player.h"

BasicEnemy::BasicEnemy(float x, float y, float direction): Enemy(x, y), GameObject(x, y, Tag::ObjectEnemy), Object(Tag::ObjectEnemy)
{
    SetDirection(direction);
    distance = GRID_SIZE*4;
    bulletColor = SDL_Color{0, 255, 0};
    sprName = "sprEnemy";
}

void BasicEnemy::Start(){
    fireRate = 2;
    health = 5;
    speed = 3;
    rotation = 180;
    counter = 0;
}

//Here is an example of how to use a counter variable to write an AI pattern
void BasicEnemy::Tick(){
    if (y > MIN_Y) {
        enemyState = EnemyState::Attack;
    }

    GameObject::Move();
    this->SetDirection(270);

    if (enemyState == EnemyState::Attack){
        GameObject::Move();
        Move();
        counter ++;
        shootTimer ++;

        speed = 1;
        canShoot = true;


        if (shootTimer >= Time::SECOND/fireRate && canShoot){
            if (Player::GetPlayer() == NULL)
                return;

            distX = Player::GetPlayer()->GetX()-GetX();
            distY = -(Player::GetPlayer()->GetY()-GetY());

            angle = std::atan2(distY, distX) * 180/M_PI;

            Instantiate(new EnemyBullet(GetX(), GetY(), bulletColor, 5, angle, GRID_SIZE * 0.80));
            rotation = -angle;
            shootTimer = 0;
        }

        if (health < 1){
            Destroy();
        }


        DestroyOutside();
    }


    ClampX();
}

void BasicEnemy::Collision(GameObject* other){

}

void BasicEnemy::Move()
{
    float c = std::cos(180 * M_PI / 180);
    float s = std::sin(180 * M_PI / 180);


    float wobble = amplitude * std::sin(frequency * counter) * frequency * Time::DELTA_TIME;

    //std::cout << (c * speed * Time::DELTA_TIME) - (s * wobble) << '\n';
    y -= (c * speed * Time::DELTA_TIME) - (s * wobble);
    x += (s * speed * Time::DELTA_TIME) - (c * wobble);
}
