#include "TrishotEnemy.h"
#include "ObjectHandler.h"
#include "EnemyBullet.h"
#include "Player.h"

//USE ME FOR TrishotING NEW ENEMY IDEAS!!! DUPLICATE AND REFACTOR WHEN DONE!!!
TrishotEnemy::TrishotEnemy(float x, float y, float direction) : Enemy(x, y), GameObject(x, y, Tag::ObjectEnemy), Object(Tag::ObjectEnemy)
{
    SetDirection(direction);
    distance = GRID_SIZE*0.8125f;

    sprName = "sprTrishotEnemy";
}

void TrishotEnemy::Start(){
    fireRate = 5;
    health = 10;
    speed = 5;
    rotation = 180;
    counter = 0;
}

//Here is an example of how to use a counter variable to write an AI pattern
void TrishotEnemy::Tick(){
    if (enemyState == EnemyState::Warmup){
        GameObject::Move();
        if (y > distance){
            SetEnemyState(EnemyState::Attack);
        }
    }

    if (enemyState == EnemyState::Attack){
        GameObject::Move();
        Move();
        counter ++;
        shootTimer ++;

        if (counter >= Time::SECOND*2) {
            canShoot = false;
            enemyState == EnemyState::Retreat;
        }
        else {
            canShoot = true;
        }

        speed = 1;
        float width = 8;


        if (shootTimer >= 60/fireRate && canShoot){
            Instantiate(new EnemyBullet(GetCenterX(), y+height, bulletColor, 5, -135, width));
            Instantiate(new EnemyBullet(GetCenterX(), y+height, bulletColor, 5, -90, width));
            Instantiate(new EnemyBullet(GetCenterX(), y+height, bulletColor, 5, -45, width));

            Instantiate(new EnemyBullet(GetCenterX(), y+height, bulletColor, 5, -30, width));
            Instantiate(new EnemyBullet(GetCenterX(), y+height, bulletColor, 5, -60, width));
            
            Instantiate(new EnemyBullet(GetCenterX(), y+height, bulletColor, 5, -120, width));
            Instantiate(new EnemyBullet(GetCenterX(), y+height, bulletColor, 5, -150, width));


            shootTimer = 0;
        }
    }


    if (enemyState == EnemyState::Retreat) {
        GameObject::Move();
        speed = 8;
        direction = 90;
        std::cout << direction << '\n';
        DestroyOutside();
    }

    if (health == 0) {
        Destroy();
    }


    ClampX();
}

void TrishotEnemy::Move()
{
    float c = std::cos(180 * M_PI / 180);
    float s = std::sin(180 * M_PI / 180);


    float wobble = amplitude * std::sin(frequency * counter) * frequency * Time::DELTA_TIME;

    //std::cout << (c * speed * Time::DELTA_TIME) - (s * wobble) << '\n';
    y -= (c * 1 * Time::DELTA_TIME) - (s * wobble);
    x += (s * 1 * Time::DELTA_TIME) - (c * wobble);
}
