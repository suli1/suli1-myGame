#ifndef _TD_GAME_MANAGER_H_
#define _TD_GAME_MANAGER_H_

#include "EnemyBase.h"
#include "TowerBase.h"

class GameManager 
{
public:
    static GameManager* getInstance();

    ~GameManager();
    void clear();
public:
    Vector<EnemyBase*>          _enemyVector;           // 地图上所有的敌人
    Vector<TowerBase*>          _towerVector;           // 地图上所有的炮塔
    Vector<Sprite*>             _bulletVector;

private:
    static GameManager*         s_shareGameManger;
};

#endif // end _TD_GAME_MANAGER_H_
