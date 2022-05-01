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
}

void Enemy::Start()
{

}

Enemy::~Enemy(){

}

void Enemy::Damage(){
    SetHealth(GetHealth()-1);
}
