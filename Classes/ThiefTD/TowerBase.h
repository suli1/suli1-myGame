#ifndef _TD_TOWER_BASE_H_
#define _TD_TOWER_BASE_H_ 

/************************************************************************/
/*  �����Ļ���                                                     */
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

    CC_SYNTHESIZE(int, _scope, Scope);          // ���������߷�Χ
    CC_SYNTHESIZE(int, _lethality, Lethality);  // ɱ����
    CC_SYNTHESIZE(int, _towerValue, TowerValue);// ��������ֵ
    CC_SYNTHESIZE(float, _rate, Rate);

protected:
    EnemyBase*          _nearesEnemy;           // ������Ұ������ĵ���
};

#endif // end _TD_TOWER_BASE_H_