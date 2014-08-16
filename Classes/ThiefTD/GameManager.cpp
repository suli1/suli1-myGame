#include "GameManager.h"


GameManager* GameManager::s_shareGameManger = nullptr;

GameManager* GameManager::getInstance()
{
    if(nullptr == s_shareGameManger) {
        s_shareGameManger = new GameManager();
    }

    return s_shareGameManger;
}

GameManager::GameManager()
    : _money(500)
    , _groupNum(10)
{

}

GameManager::~GameManager()
{
    clear();
    CC_SAFE_DELETE(s_shareGameManger);
}

void GameManager::clear()
{
    _enemyVector.clear();
    _towerVector.clear();
}