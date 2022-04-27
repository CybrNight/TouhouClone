#include "EnemySpawner.h"
#include "ObjectHandler.h"
#include "Game.h"
#include "BurstEnemy.h"
#include "BasicEnemy.h"
#include "TrishotEnemy.h"
#include "TestEnemy.h"
#include <random>


EnemySpawner::EnemySpawner(): Object()
{
    counter = 0;
}

void EnemySpawner::GenerateWave()
{
    int type = std::rand() % 4;
    float y=-32;
    int num, range = (MAX_X - GRID_SIZE*4) + (MIN_X + GRID_SIZE*4) ;
    
    std::cout << "EnemySpawner: Generating wave type (" << type << ")\n";
    switch (type){ //Different wave types
    case 0:
        spawnInterval = 0.5;
        waveTime = 6;
        for (int i = 0; i < 5; i++){
            num = rand() % range;

            enemyQueue.push_back(new BasicEnemy(num, y));
        }
        break;
    case 1:
        waveTime = 12;
        spawnInterval = 0.5;
        for (int x = MIN_X + GRID_SIZE * 4; x <= MAX_X-(GRID_SIZE*4); x += GRID_SIZE){
            enemyQueue.push_back(new BurstEnemy(x, y));
        }
        break;
    case 2:
        waveTime = 14;
        spawnInterval = 0.75f;
        for (int i = 0; i < 5; i++){
            num = rand() % range;

            enemyQueue.push_back(new BurstEnemy(num, y));
        }


        for (int i = 0; i < 2; i++){
            num = rand() % range;

            enemyQueue.push_back(new BasicEnemy(num, y));
        }
        break;
    case 3:
        spawnInterval = 0.5;
        waveTime = 10;
        enemyQueue.push_back(new TrishotEnemy((GAME_WIDTH/2)-GRID_SIZE*3, y));
        enemyQueue.push_back(new TrishotEnemy((GAME_WIDTH/2)+GRID_SIZE*3, y));

        enemyQueue.push_back(new BurstEnemy(GAME_WIDTH/2 + GRID_SIZE, y));
        enemyQueue.push_back(new BurstEnemy(GAME_WIDTH/2 + GRID_SIZE, y+GRID_SIZE));
    }
    std::cout << "EnemySpawner: Adding new wave to queue\n";
    canSpawn = true;
}

void EnemySpawner::Start()
{
    canSpawn = true;
    std::srand(std::time(nullptr));
    counter = 0;
    GenerateWave();
}

void EnemySpawner::Tick(){

    if (!enemyQueue.empty() && canSpawn){
        if (counter >= 60*spawnInterval){
            std::cout << "EnemySpawner: Spawned enemy from enemyQueue\n";
            activeEnemies.push_back(dynamic_cast<GameObject*>(Instantiate(enemyQueue.back())));
            enemyQueue.pop_back();
            counter = 0;
            if (enemyQueue.empty()){
                canSpawn = false;
                counter = 0;
            }
        }
    }
    counter ++;


    if (!canSpawn){
        if (counter >= Time::SECOND/2 && activeEnemies.empty()){
            GenerateWave();
        }
    }

    for (size_t i = 0; i < activeEnemies.size(); i++){
        GameObject* temp = activeEnemies.at(i);
        if (temp != NULL && temp->IsDestroyed()){
            activeEnemies.erase(activeEnemies.begin() + i);
        }
    }
}

void EnemySpawner::TickSecond()
{

}
