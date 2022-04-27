#include "Enemy.h"
#include "ObjectHandler.h"


Enemy::Enemy(float x, float y): GameObject(x, y, Tag::ObjectEnemy), Object(Tag::ObjectEnemy)
{
    
}

void Enemy::Init(){
    shootTimer = 0;
    fireRate = 15;
    canShoot = false;
    shootTimer = 0;
    enemyState = EnemyState::Warmup;
    Start();
}

void Enemy::Start()
{

}

Enemy::~Enemy(){

}

void Enemy::Damage(){
    set_health(get_health()-1);
}
