#include "TowerBase.h"
#include "GameManager.h"


TowerBase::TowerBase()
    : _scope(0)
    , _lethality(0)
    , _rate(0.0f)
    , _nearesEnemy(nullptr)
{

}

bool TowerBase::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(!Sprite::init());

        bRet = true;
    } while (0);

    return bRet;
}

void TowerBase::checkNearesEnemy()
{
    auto vEnemy = GameManager::getInstance()->_enemyVector;
    auto currMinDistant = this->_scope;

    EnemyBase* enemyTemp = nullptr;

    for(int i = 0; i < vEnemy.size(); i++) {
        auto enemy = vEnemy.at(i);
        auto distance = this->getPosition().getDistance(enemy->getSpriteBody()->getPosition());

        if(distance < currMinDistant) {
            currMinDistant = distance;
            enemyTemp = enemy;
        }
    }

    _nearesEnemy = enemyTemp;
}


