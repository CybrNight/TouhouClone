#pragma once

#include <gameobject.h>
#include "enemy.h"
#include "player.h"

class BurstEnemy : public virtual Enemy
{
    float startY = 0;

protected:
    void tick();
    void start();
public:
    BurstEnemy(float x, float y, float direction = 270);
    ~BurstEnemy(){}


    //Called when other Collider overlaps
    void collision(GameObject* other);
};