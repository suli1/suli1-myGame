#include "ArrowTower.h"
#include "GameManager.h"

ArrowTower::ArrowTower()
    : _roateArrow(nullptr)
{

}

bool ArrowTower::init()
{
    bool bRet = false;

    do 
    {
        CC_BREAK_IF(!TowerBase::init());

        this->setScope(90);
        this->setLethality(2);
        this->setTowerValue(250);
        this->setRate(2);


        // 塔的底座
        auto baseplate = Sprite::createWithSpriteFrameName("baseplate.png");
        this->addChild(baseplate);

        // 可旋转的弓
        _roateArrow = Sprite::createWithSpriteFrameName("arrow.png");
        _roateArrow->setPosition(0, baseplate->getContentSize().height/4);
        this->addChild(_roateArrow);

        this->schedule(schedule_selector(ArrowTower::roateAndShoot), 0.8f);

        bRet = true;
    } while (0);

    return bRet;
}


void ArrowTower::roateAndShoot(float dt)
{
    this->checkNearesEnemy();

    if(_nearesEnemy) {
        auto roateVector = _nearesEnemy->getSpriteBody()->getPosition() - this->getPosition();
        float roateRadinas = roateVector.getAngle();
        float roateDegrees = CC_RADIANS_TO_DEGREES(-1 * roateRadinas);

        float speed = 0.5/M_PI;
        float roateDuration = fabs(roateRadinas * speed);

        _roateArrow->runAction(Sequence::create(RotateTo::create(roateDuration, roateDegrees),
            CallFunc::create(CC_CALLBACK_0(ArrowTower::shoot, this)),
            nullptr));
    }

}

Sprite* ArrowTower::bullet()
{
    auto arrowBullet = Sprite::createWithSpriteFrameName("arrowBullet.png");
    arrowBullet->setPosition(_roateArrow->getPosition());
    arrowBullet->setRotation(_roateArrow->getRotation());
    this->addChild(arrowBullet);

    return arrowBullet;
}

void ArrowTower::shoot()
{
    auto vBullets = GameManager::getInstance()->_bulletVector;
    if(_nearesEnemy && _nearesEnemy->getCurrHp() > 0) {
        auto currBullet = bullet();
        GameManager::getInstance()->_bulletVector.pushBack(currBullet);

        auto moveDuration = this->getRate();
        auto shootVec = _nearesEnemy->getSpriteBody()->getPosition() - this->getPosition();
        auto normalizedShootVec = -shootVec.getNormalized();

        auto farthesDistance = Director::getInstance()->getWinSize().width;
        auto overShootVec = normalizedShootVec * farthesDistance;
        auto offScreenPoint = (_roateArrow->getPosition() - overShootVec);

        currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offScreenPoint),
                                               CallFuncN::create(CC_CALLBACK_1(ArrowTower::removeBullet, this)),
                                               nullptr));
        currBullet = nullptr;
    }
}

void ArrowTower::removeBullet(Node* pSender)
{
    Sprite* sprite = (Sprite*)pSender;
    GameManager::getInstance()->_bulletVector.eraseObject(sprite);
    sprite->removeFromParent();
}
