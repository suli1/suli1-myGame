#include "Thief.h"


bool Thief::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(!EnemyBase::init());

        // 初始化基本数值
        this->setMaxHp(10);
        this->setCurrHp(this->getMaxHp());
        this->setRunSpeed(25);

        this->_spriteBody = Sprite::createWithSpriteFrameName("enemyRight1_1.png");
        this->addChild(_spriteBody);

        // 加载动画入缓存

        // 1.敌人向右移动
        _animationRight = this->createAnimation("enemyRight1", 4, 0.1f);
        AnimationCache::getInstance()->addAnimation(_animationRight, "runright1");

        // 2.敌人向左移动
        _animationLeft = this->createAnimation("enemyLeft1", 4, 0.1f);
        AnimationCache::getInstance()->addAnimation(_animationRight, "runleft1");

        // 3.敌人被打爆
        _animationExplode = this->createAnimation("explode1", 6, 0.15f);
        AnimationCache::getInstance()->addAnimation(_animationExplode, "explode1");

        this->createAndSetHpBar();

        this->schedule(schedule_selector(EnemyBase::changeDirection), 0.4f);

        bRet = true;
    } while (0);

    return bRet;
}

Thief* Thief::create(const Vector<Node*>& points)
{
    Thief* pRet = new Thief();
    if(pRet && pRet->init()) {
        pRet->setPointsVector(points);
        pRet->runFllowPoint();
        pRet->autorelease();
    } else {
        delete pRet;
        pRet = nullptr;
    }

    return pRet;
}

void Thief::changeDirection(float dt)
{
    auto curr = currPoint();
    if(nullptr == curr) {
        return ;
    }

    if(curr->getPositionX() > _spriteBody->getPositionX()) {
        _spriteBody->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("runright1")));
    } else {
        _spriteBody->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("runleft1")));
    }
}


void Thief::enemyExpload()
{
    _spriteHpBg->setVisible(false);
    _spriteBody->stopAllActions();

    this->unschedule(schedule_selector(Thief::changeDirection));

    _spriteBody->setAnchorPoint(Point(0.5f, 0.25f));
    _spriteBody->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("explode1")),
                                            CallFunc::create(CC_CALLBACK_0(EnemyBase::removeFromParent, this)),
                                            nullptr));

}
