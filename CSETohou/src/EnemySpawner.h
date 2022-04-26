#pragma once


#include "gameobject.h"
#include <vector>

class EnemySpawner: public virtual Object
{
    bool canSpawn = false;
    float counter = 0;
    float spawnInterval = 0.8;
    float waveTime = 0;

    std::vector<GameObject*> enemyQueue;
    std::vector<GameObject*> activeEnemies;

    void generate_wave();


protected:
    void start();
    void tick();
    void tick_second();

public:
    EnemySpawner();
    ~EnemySpawner(){enemyQueue.clear();}
};