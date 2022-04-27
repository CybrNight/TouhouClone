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

    void GenerateWave();


protected:
    void Start();
    void Tick();
    void TickSecond();

public:
    EnemySpawner();
    ~EnemySpawner(){enemyQueue.clear();}
};