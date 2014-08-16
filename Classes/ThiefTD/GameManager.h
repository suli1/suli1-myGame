#ifndef _TD_GAME_MANAGER_H_
#define _TD_GAME_MANAGER_H_

#include "EnemyBase.h"
#include "TowerBase.h"

class GameManager 
{
public:
    static GameManager* getInstance();

    void clear();
protected:
    GameManager();
    ~GameManager();
public:
    Vector<EnemyBase*>          _enemyVector;           // 地图上所有的敌人
    Vector<TowerBase*>          _towerVector;           // 地图上所有的炮塔
    Vector<Sprite*>             _bulletVector;

private:
    static GameManager*         s_shareGameManger;

    CC_SYNTHESIZE(int, _money, Money);
    CC_SYNTHESIZE(int, _groupNum, GroupNum);            // 当前关卡敌人进攻波数
};

#endif // end _TD_GAME_MANAGER_H_
