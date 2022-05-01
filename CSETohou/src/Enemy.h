#pragma once

#include "GameObject.h"
#include "IDamagable.h"

enum class EnemyState{
    Warmup,
    Attack,
    Retreat,
    Standby,
};

class Enemy : public virtual GameObject, public virtual IDamagable
{
protected:
    //All enemies have health
    float health = 5;

    float shootTimer = 0;
    float fireRate = 0;
    float counter = 0;

    float distX = 0, distY = 0;
    float angle = 0;

    EnemyState enemyState = EnemyState::Warmup;

    bool canShoot = false;
    SDL_Color bulletColor = SDL_Color{255, 0 ,0};


public:
    Enemy(float x, float y);
    virtual ~Enemy() = 0;
    virtual void Init();
    void Damage();
    void Start();

    inline void SetCanShoot(bool canShoot) {this->canShoot = canShoot;}
    inline void SetEnemyState(EnemyState enemyState) {this->enemyState = enemyState;}
    inline void SetHealth(float health){this->health = health;}

    inline float GetHealth(){return health;}
    inline bool CanShoot() const {return canShoot;}
    inline const SDL_Color GetBulletColor() const {return bulletColor;}
    inline const EnemyState GetEnemyState() const {return enemyState;}
};