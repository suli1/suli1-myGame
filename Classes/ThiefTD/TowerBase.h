#ifndef _TD_TOWER_BASE_H_
#define _TD_TOWER_BASE_H_ 

/************************************************************************/
/*  炮塔的基类                                                     */
/************************************************************************/

#include "EnemyBase.h"

class TowerBase : public Sprite
{
protected:
    TowerBase();

    virtual bool init() override;

    //CREATE_FUNC(TowerBase);

    void checkNearesEnemy();

    virtual Sprite* bullet() = 0;
    virtual void shoot() = 0;
    virtual void removeBullet(Node* pSender) = 0;

    CC_SYNTHESIZE(int, _scope, Scope);          // 炮塔的视线范围
    CC_SYNTHESIZE(int, _lethality, Lethality);  // 杀伤力
    CC_SYNTHESIZE(int, _towerValue, TowerValue);// 塔的生命值
    CC_SYNTHESIZE(float, _rate, Rate);

protected:
    EnemyBase*          _nearesEnemy;           // 炮塔视野内最近的敌人
};

#endif // end _TD_TOWER_BASE_H_