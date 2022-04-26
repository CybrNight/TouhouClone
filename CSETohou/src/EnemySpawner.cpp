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

void EnemySpawner::generate_wave()
{
    int type = 3;
    float y=-32;
    int num, range = (MAX_X - GRID_SIZE*4) + (MIN_X + GRID_SIZE*4) ;
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

void EnemySpawner::start()
{
    canSpawn = false;
    std::srand(std::time(nullptr));
}

void EnemySpawner::tick(){

    if (!enemyQueue.empty() && canSpawn){
        if (counter >= 60*spawnInterval){
            std::cout << "EnemySpawner: Spawned enemy from enemyQueue\n";
            activeEnemies.push_back(dynamic_cast<GameObject*>(instantiate(enemyQueue.back())));
            enemyQueue.pop_back();
            counter = 0;
            if (enemyQueue.empty()){
                canSpawn = false;
            }
        }
    }
    counter ++;


    if (!canSpawn){
        if (counter > 60*waveTime/2 && counter <= 60*waveTime){
            for (auto i = activeEnemies.begin(); i != activeEnemies.end(); i++){
                dynamic_cast<Enemy*>(*i)->set_enemy_state(EnemyState::Retreat);
            }
        }else if (counter >= 60*waveTime){
            counter = 0;
            generate_wave();
        }else if (activeEnemies.empty()){
            counter += 60*(waveTime/4);
        }
    }

    for (size_t i = 0; i < activeEnemies.size(); i++){
        GameObject* temp = activeEnemies.at(i);
        if (temp != NULL && temp->is_destroyed()){
            activeEnemies.erase(activeEnemies.begin() + i);
        }
    }
}

void EnemySpawner::tick_second()
{

}
