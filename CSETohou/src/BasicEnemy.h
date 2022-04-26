#pragma once

#include <enemy.h>
#include <iostream>

//USE ME FOR BasicING NEW ENEMY IDEAS!!! DUPLICATE AND REFACTOR WHEN DONE!!!
class BasicEnemy : public virtual Enemy
{
    float distance = 0;
    float amplitude = GRID_SIZE*2;
    float frequency = 2.5;

protected:
    void tick();
    void start();
public:
    BasicEnemy(float x, float y, float direction = 270);
    ~BasicEnemy(){std::cout << "Destroyed BasicEnemy\n";}

    void collision(GameObject* other);

    void move();
};
