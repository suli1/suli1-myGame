#ifndef _TD_ARROW_TOWER_H_
#define _TD_ARROW_TOWER_H_

#include "TowerBase.h"


class ArrowTower : public TowerBase
{
public:
    CREATE_FUNC(ArrowTower);
protected:
    ArrowTower();

    virtual bool init() override;

    void roateAndShoot(float dt);

    virtual Sprite* bullet();

    virtual void shoot();

    virtual void removeBullet(Node* pSender);

private:
    Sprite*             _roateArrow;            // 可以旋转的弓
};


#endif // end _TD_ARROW_TOWER_H_