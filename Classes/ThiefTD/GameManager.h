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
    Vector<EnemyBase*>          _enemyVector;           // ��ͼ�����еĵ���
    Vector<TowerBase*>          _towerVector;           // ��ͼ�����е�����
    Vector<Sprite*>             _bulletVector;

private:
    static GameManager*         s_shareGameManger;

    CC_SYNTHESIZE(int, _money, Money);
    CC_SYNTHESIZE(int, _groupNum, GroupNum);            // ��ǰ�ؿ����˽�������
};

#endif // end _TD_GAME_MANAGER_H_
