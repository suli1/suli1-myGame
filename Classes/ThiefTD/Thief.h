#ifndef _TD_THIEF_H_
#define  _TD_THIEF_H_

#include "EnemyBase.h"

class Thief : public EnemyBase
{
public:
    static Thief* create(const Vector<Node*>& points);
protected:
    virtual bool init() override;

    virtual void changeDirection(float dt) override;

public:
    virtual void enemyExpload() override;
};


#endif // end _TD_THIEF_H_
