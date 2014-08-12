#include "PlayLayer.h"
#include "Thief.h"
#include "ArrowTower.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"
#include "platform/CCFileUtils.h"


#define MAP_WIDTH       16
#define MAP_HEIGHT      9


PlayLayer::PlayLayer()
    : _bgLayer(nullptr)
    , _chooseTowerPanel(nullptr)
    , _map(nullptr)
    , _objects(nullptr)
    , _offX(0.0f)
    , _money(500)
    , _towerMatrix(nullptr)
{

}

PlayLayer::~PlayLayer()
{
    CC_SAFE_DELETE_ARRAY(_towerMatrix);
}

bool PlayLayer::init()
{
    bool bRet = false;

    do 
    {
        CC_BREAK_IF(!Layer::init());

        auto winSize = Director::getInstance()->getWinSize();

        // 加载地图背景
        auto gameBg = Sprite::create("playbg.png");
        gameBg->setPosition(Point(winSize.width/2, winSize.height/2));
        this->addChild(gameBg, ZORDER_BG);


        // 加载瓦片地图
        _map = TMXTiledMap::create("tilemap0.tmx");

        _bgLayer = _map->getLayer("bg");
        _bgLayer->setAnchorPoint(Point(0.5f, 0.5f));
        _bgLayer->setPosition(winSize.width/2, winSize.height/2);

        _objects = _map->getObjectGroup("obj");
        this->addChild(_map, ZORDER_MAP);

        // 加载Sprite缓存
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Play.plist");

        // 计算瓦片地图到屏幕的x轴偏移
        _offX = (_map->getContentSize().width - winSize.width)/2;
        initPointsVector(_offX);

       
        // 添加触摸响应
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->onTouchBegan = CC_CALLBACK_2(PlayLayer::onTouchBegan, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

        this->scheduleUpdate();

        this->schedule(schedule_selector(PlayLayer::logic), 2.0f);

        // 初始化防御塔位置记录矩阵
        _towerMatrix = new TowerBase*[MAP_WIDTH * MAP_HEIGHT];
        memset(_towerMatrix, 0, sizeof(TowerBase*)*(MAP_WIDTH*MAP_HEIGHT));

        bRet = true;
    } while (0);


    return bRet;
}

void PlayLayer::initPointsVector(float offX)
{
    Node* runOfPoint = nullptr;

    int count = 0;
    ValueMap point;
    point = _objects->getObject(std::to_string(count));

    while(point.begin() != point.end())
    {
        float x = point.at("x").asFloat();
        float y = point.at("y").asFloat();

        runOfPoint = Node::create();
        runOfPoint->setPosition(x - offX, y);
        _vPoints.pushBack(runOfPoint);
        
        count++;
        point = _objects->getObject(std::to_string(count));
    }

    runOfPoint = nullptr;
}

bool PlayLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    if(_chooseTowerPanel) {
        this->removeChild(_chooseTowerPanel);
        _chooseTowerPanel = nullptr;
    }
    auto location = touch->getLocation();
    checkAndAddTowerPanle(location);

    return true;
}

void PlayLayer::update(float delay)
{
    //  添加防御塔
    addTower();

    collisionDetection();
}

void PlayLayer::addTowerChoosePanel(Point position)
{
    _chooseTowerPanel = TowerPanelLayer::create();
    _chooseTowerPanel->setPosition(position);
    this->addChild(_chooseTowerPanel, ZORDER_PLANEL);
}

void PlayLayer::checkAndAddTowerPanle(Point position)
{
    Point towerCoord = convertToTileCoord(position);
    Point matrixCoord = convertToMatrixCoord(position);

    int gid = _bgLayer->getTileGIDAt(towerCoord);
    auto value = _map->getPropertiesForGID(gid);
    int TouchValue;
    if(value.getType() == Value::Type::MAP) {
        TouchValue = value.asValueMap().at("canTouch").asInt();
    } else {
        TouchValue = 0;
    }

    int MatrixIndex = (int)(matrixCoord.y * MAP_WIDTH + matrixCoord.x);
    auto tileWidth = _map->getContentSize().width / _map->getMapSize().width;
    auto tileHeight = _map->getContentSize().height / _map->getMapSize().height;
    _towerPos = Point( (towerCoord.x * tileWidth) + tileWidth/2 - _offX, _map->getContentSize().height - (towerCoord.y *tileHeight) - tileHeight/2 );
    if(1 == TouchValue && NULL == _towerMatrix[MatrixIndex]) {
        addTowerChoosePanel(_towerPos);
    } else {
        auto tips = Sprite::createWithSpriteFrameName("no.png");
        tips->setPosition(_towerPos);
        this->addChild(tips);
        tips->runAction(Sequence::create(DelayTime::create(0.8f),
                                         CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
                                         nullptr));
    }


}

Point PlayLayer::convertToTileCoord(Point position)
{
    int x = (position.x + _offX) / _map->getContentSize().width * _map->getMapSize().width;
    int y = _map->getMapSize().height - position.y / _map->getContentSize().height * _map->getMapSize().height;

    return Point(x, y);
}

Point PlayLayer::convertToMatrixCoord(Point position)
{
    int x = (position.x + _offX) / _map->getContentSize().width * _map->getMapSize().width;
    int y = position.y / _map->getContentSize().height * _map->getMapSize().height;

    return Point(x, y);
}


void PlayLayer::addTower()
{
    if(_chooseTowerPanel) {
        auto type = _chooseTowerPanel->getChooseTowerType();
        if(type == TowerType::ANOTHER) {
            return;
        }

        Point matrixCoord = convertToMatrixCoord(_towerPos);
        int matrixIndex = static_cast<int>(matrixCoord.y * MAP_WIDTH + matrixCoord.x);
        bool noMoneyTips = false;
        TowerBase* tower = nullptr;

        if(type == TowerType::ARROW_TOWER) {
            if(_money >= 200) {
                tower = ArrowTower::create();
                _money -= 200;
            } else {
                noMoneyTips = true;
            }

        } else if(type == TowerType::ATTACK_TOWER){
            if(_money >= 150) {
                //tower = AttackTower::create();
                _money -= 150;
            } else {
                noMoneyTips = true;
            }

        } else if(type == TowerType::MULTIDIR_TOWER) {
            if(_money >= 250) {
                //tower = MultiDirTower::create();
            } else {
                noMoneyTips = true;
            }
        }

        if(tower) {
            tower->setPosition(_towerPos);
            tower->runAction(Sequence::create(FadeIn::create(1.0f), nullptr));
            this->addChild(tower);
            GameManager::getInstance()->_towerVector.pushBack(tower);
            _towerMatrix[matrixIndex] = tower;
        }

        type = TowerType::ANOTHER;
        _chooseTowerPanel->setChooseTowerType(type);
        this->removeChild(_chooseTowerPanel);
        _chooseTowerPanel = nullptr;
        if(noMoneyTips) {
            auto tips = Sprite::createWithSpriteFrameName("nomoney_mark.png");
            tips->setPosition(_towerPos);
            this->addChild(tips);
            tips->runAction(Sequence::create(DelayTime::create(0.5f),
                                            CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
                                            nullptr));
        }


    }
}


void PlayLayer::addEnemy()
{
    // 添加一个小偷测试
    auto thief =  Thief::create(_vPoints);
    this->addChild(thief, ZORDER_THIEF);
    GameManager::getInstance()->_enemyVector.pushBack(thief);

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);

}

void PlayLayer::collisionDetection()
{
    auto gameManager = GameManager::getInstance();
    auto vBullets = gameManager->_bulletVector;
    auto vEnemies = gameManager->_enemyVector;
    if(vBullets.empty() || vEnemies.empty()) {
        return;
    }

    // 对所每一个子弹相对与每一个敌人做检测

    Vector<EnemyBase*> vEnemyNeedToDel;
    Vector<Sprite*> vBulletNeedToDel;


    for(int i = 0; i < vBullets.size(); i++) {
        Sprite* bullet = vBullets.at(i);
        Rect bulletRect(bullet->getPositionX() + bullet->getParent()->getPositionX() - bullet->getContentSize().width/2,
                        bullet->getPositionY() + bullet->getParent()->getPositionY() - bullet->getContentSize().height/2,
                        bullet->getContentSize().width,
                        bullet->getContentSize().height );

        for(int j = 0; j < vEnemies.size(); j++) {
            EnemyBase* enemy = vEnemies.at(i);
            Rect enemyRect = enemy->getSpriteBody()->getBoundingBox();

            if(bulletRect.intersectsRect(enemyRect)) {
                // 子弹与敌人碰撞, 退出循环，遍历下一个子弹
                vEnemyNeedToDel.pushBack(enemy);

                vBulletNeedToDel.pushBack(bullet);
                break;
            }

        }
    }

    for(EnemyBase* enemyTemp : vEnemyNeedToDel) {
        enemyTemp->enemyExpload();
        gameManager->_enemyVector.eraseObject(enemyTemp);

    }
    vEnemyNeedToDel.clear();


    for(Sprite* bulletTemp : vBulletNeedToDel) {
        gameManager->_bulletVector.eraseObject(bulletTemp);
        bulletTemp->removeFromParent();
    }
    vBulletNeedToDel.clear();

}

void PlayLayer::logic(float dt)
{
    addEnemy();
}

