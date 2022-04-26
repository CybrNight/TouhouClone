#pragma once

#include <enemy.h>
#include "IDamagable.h"
#include <iostream>

//USE ME FOR TrishotING NEW ENEMY IDEAS!!! DUPLICATE AND REFACTOR WHEN DONE!!!
class TrishotEnemy : public virtual Enemy
{
    float distance = 0;
    float amplitude = GRID_SIZE;
    float frequency = 6;

protected:
    void tick();
    void start();
public:
    TrishotEnemy(float x, float y, float direction = 270);
    ~TrishotEnemy(){std::cout << "Destroyed TrishotEnemy\n";}

    void move();
};