#pragma once

#include "enemy.h"
#include <iostream>

//USE ME FOR TESTING NEW ENEMY IDEAS!!! DUPLICATE AND REFACTOR WHEN DONE!!!
class TestEnemy : public virtual Enemy
{
    float distance = 0;
    float amplitude = GRID_SIZE;
    float frequency = 6;

protected:
    void Tick();
    void Start();
public:
    TestEnemy(float x, float y, float direction = 270);
    ~TestEnemy(){ std::cout << "Destroyed BasicEnemy\n";}

    void Collision(GameObject* other);

    void Move();
};