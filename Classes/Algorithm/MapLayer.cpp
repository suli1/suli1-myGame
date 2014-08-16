#include "MapLayer.h"
#include "AstarItem.h"


#define kTagTileMap 100

MapLayer::MapLayer()
    : _tamara(nullptr)
    , _path(nullptr)
    , _vmove(0)
    , _hmove(0)
    , _stepIndex(0)
    , _smallStepIndex(0)
{

}

MapLayer::~MapLayer()
{
    CC_SAFE_DELETE(_myAstar);

}

bool MapLayer::init()
{
    bool bRet = false;

    do 
    {
        CC_BREAK_IF(!Layer::init());

        Size winSize = Director::getInstance()->getWinSize();

        // 初始化地图
        TMXTiledMap* map = TMXTiledMap::create("iso-test-zorder.tmx");
        map->setPosition((winSize.width - map->getContentSize().width)/2, 0);
        this->addChild(map, 0, kTagTileMap);

        // 初始化任务
        _tamara = Sprite::create("grossinis_sister1.png");
        map->addChild(_tamara, map->getChildren().size());
        _tamara->retain();
        int mapWidth = map->getMapSize().width * map->getTileSize().width;
        int mapHeight = map->getMapSize().height * map->getTileSize().height;
        _tamara->setPosition(mapWidth/2, 112);
        _tamara->setAnchorPoint(Point(0.5f, 0));
        

        _vmove = -1;
        _hmove = -1;
        _stepIndex = -1;
        _myAstar = new Astar();

        this->scheduleUpdate();

        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = CC_CALLBACK_2(MapLayer::onTouchBegan, this);
        this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

        bRet = true;
    } while (0);

    return bRet;
}


bool MapLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    Point beginPos = touch->getLocationInView();
    beginPos = Director::getInstance()->convertToGL(beginPos);

    TMXTiledMap* map = (TMXTiledMap*)this->getChildByTag(kTagTileMap);

    // 获取触摸点在地图位置上的索引
    Point mapPos = map->getPosition();
    Point aimMapIndex = convertTo2d(Point(beginPos.x - mapPos.x, beginPos.y - mapPos.y));
    if(aimMapIndex.x < 0 || aimMapIndex.y < 0 || aimMapIndex.x >= map->getMapSize().width || aimMapIndex.y >= map->getMapSize().height) {
        // 超出地图边界
        return false;
    }

    Point herop = _tamara->getPosition();
    Point mapIndex = convertTo2d(herop);
    TMXLayer* layer = map->getLayer("grass");
    int tilegid = layer->getTileGIDAt(aimMapIndex);
    Value tileValue = map->getPropertiesForGID(tilegid);
    int touchValue = tileValue.asValueMap().at("conflict").asInt();
    if(touchValue == 1) {
        return false;
    }

    _path = _myAstar->findPath(mapIndex.x, mapIndex.y, aimMapIndex.x, aimMapIndex.y, map);
    if(nullptr != _path && _path->count() >= 2) {
        _stepIndex = 1;
    } else {
        _stepIndex = -1;
    }
    _smallStepIndex = 0;

    return true;
}


void MapLayer::update(float dt)
{

    // 根据路径移动
    if(_stepIndex >= 1) {

        if(_smallStepIndex == 0) {
            int ncol = ((AstarItem*)_path->getObjectAtIndex(_stepIndex))->getCol();
            int nrow = ((AstarItem*)_path->getObjectAtIndex(_stepIndex))->getRow();
            int pcol = ((AstarItem*)_path->getObjectAtIndex(_stepIndex - 1))->getCol();
            int prow = ((AstarItem*)_path->getObjectAtIndex(_stepIndex - 1))->getRow();

            if(pcol == ncol) {
                if(prow > nrow) {
                    _vmove = 2;

                } else if(prow <nrow) {
                    _vmove = 3;

                } else {
                    _vmove = -1;
                }
            } else if(prow == nrow) {
                if(pcol > ncol) {
                    _vmove = 1;

                } else if(pcol < ncol) {
                    _vmove = 0;

                } else {
                    _vmove = -1;
                }
            } else {
                _vmove = -1;
            }

        }

        Point herop = _tamara->getPosition();

        switch(_vmove) {
        case 0:
            herop.x += 1;
            herop.y -= 0.5;
            break;
        case 1:
            herop.x -= 1;
            herop.y += 0.5;
            break;
        case 2:
            herop.x += 1;
            herop.y += 0.5;
            break;
        case 3:
            herop.x -= 1;
            herop.y -= 0.5;
            break;
        case 4:
            herop.x += 1;
            break;
        case 5:
            herop.x -= 1;
            break;
        case 6:
            herop.y += 0.5;
            break;
        case 7:
            herop.y -= 0.5;
            break;
        default:
            break;
        }

        _smallStepIndex++;
        if(_smallStepIndex >= 32) {
            _smallStepIndex = 0;
            if(_stepIndex >= _path->count() - 1) {
                // 移动到终点
                _stepIndex = -1;
                _vmove = -1;

                _path->removeAllObjects();
                _path->release();
                _path = nullptr;

            } else {
                _stepIndex++;
                _vmove = -1;
            }
        }

        _tamara->setPosition(herop);

        // 地图随主角移动
        auto map = (TMXTiledMap*)this->getChildByTag(kTagTileMap);
        int mapWidth = map->getMapSize().width * map->getTileSize().width;
        int mapHeight = map->getMapSize().height * map->getTileSize().height;
        float deltaX = herop.x - mapWidth/2;
        float deltaY = herop.y - 112;
        auto winSize = Director::getInstance()->getWinSize();
        map->setPosition((winSize.width - map->getContentSize().width)/2 - deltaX, -deltaY);

    }
}


Point MapLayer::convertTo2d(Point position)
{
    TMXTiledMap* map = (TMXTiledMap*) getChildByTag(kTagTileMap);
    int mapWidth = map->getMapSize().width * map->getTileSize().width;
    int mapHeight = map->getMapSize().height * map->getTileSize().height;

    int x = position.x;
    int y = position.y;

    double distanse;
    double sin1;
    double sin11;
    double sin22;
    double cos11;
    double cos1;
    int d2x;
    int d2y;
    double mystatic5 = sqrt(5.0);
    double mystatic = 16 * mystatic5;
    //char mch[256];

    if(x > mapWidth/2){
        distanse = sqrt((x - mapWidth/2) * (x - mapWidth/2) + (mapHeight - y) * (mapHeight - y));
        sin1 = (mapHeight - y)/distanse;
        cos1 = (x - mapWidth/2)/distanse;
        sin11 = (sin1 * 2 - cos1) / mystatic5;
        cos11 = (sin1 + cos1 * 2) / mystatic5;
        d2y = distanse * 5 / 4 * sin11 / mystatic;
        sin22 = (2 * sin1 + cos1) / mystatic5;
        d2x = distanse * 5 / 4 * sin22 / mystatic;
        return Point(d2x,d2y);

    }else{
        distanse = sqrt((mapWidth/2 - x) * (mapWidth/2 - x) + (mapHeight - y) * (mapHeight - y));
        sin1 = (mapHeight - y)/distanse;
        cos1 = (mapWidth/2 - x)/distanse;
        sin11 = (sin1 * 2 - cos1) / mystatic5;
        cos11 = (sin1 + cos1 * 2) / mystatic5;
        d2x = distanse * 5 / 4 * sin11 / mystatic;
        //sin22 = 4.0 * cos11 / 5 + 3.0 * sin11 / 5;
        sin22 = (2 * sin1 + cos1) / mystatic5;
        d2y = distanse * 5 / 4 * sin22 / mystatic;
        return Point(d2x,d2y);
    }

}

