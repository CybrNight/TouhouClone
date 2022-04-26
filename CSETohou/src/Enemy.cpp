#include "Enemy.h"
#include "ObjectHandler.h"

Enemy::Enemy(float x, float y): GameObject(x, y, Tag::ObjectEnemy), Object(Tag::ObjectEnemy)
{

}

void Enemy::init(){
    shootTimer = 0;
    fireRate = 15;
    canShoot = false;
    shootTimer = 0;
    enemyState = EnemyState::Warmup;
    start();
}

void Enemy::start()
{

}

Enemy::~Enemy(){

}

void Enemy::damage(){
    set_health(get_health()-1);
}
