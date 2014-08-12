#include "BulletLayer.h"
#include "PlaneLayer.h"

bool BulletLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Layer::init());

		auto texture = TextureCache::getInstance()->textureForKey("shoot.png");
		_bulletBatchNode = SpriteBatchNode::createWithTexture(texture);
		this->addChild(_bulletBatchNode);



		bRet = true;
	} while (0);

	return bRet;
}

void BulletLayer::addBullet(float dt)
{
	auto bullet = Sprite::createWithSpriteFrameName("bullet1.png");
	auto planePosition = PlaneLayer::getInstance()->getChildByTag(AIRPLANE)->getPosition();
	auto bulletPosition = Vec2(planePosition.x, planePosition.y + PlaneLayer::getInstance()->getChildByTag(AIRPLANE)->getContentSize().height/2);
	bullet->setPosition(bulletPosition);
	_bulletBatchNode->addChild(bullet);
	_vAllBullet.pushBack(bullet);

	// ×Óµ¯µÄ·ÉÐÐ¾àÀë£¬³¬³öÆÁÄ»¼´½áÊø
	float length = Director::getInstance()->getWinSize().height + bullet->getContentSize().height/2 - bulletPosition.y;
	float velocity = 420/1;
	float realMoveDuration = length/velocity;

	FiniteTimeAction* actionMove = MoveTo::create(realMoveDuration, Vec2(bulletPosition.x, Director::getInstance()->getWinSize().height + bullet->getContentSize().height/2));
	FiniteTimeAction* actionDone = CallFuncN::create(this, callfuncN_selector(BulletLayer::bulletMoveFinished));

	auto sequence = Sequence::create(actionMove, actionDone, nullptr);

	bullet->runAction(sequence);
}

void BulletLayer::bulletMoveFinished(Node* pSender)
{
	auto bullet = (Sprite*)pSender;

	Vector<Sprite*>::iterator iter = _vAllBullet.find(bullet);
	if(iter != _vAllBullet.end()) {
		_vAllBullet.erase(iter);
		_bulletBatchNode->removeChild(bullet, true);
	}
}

void BulletLayer::startShoot(float delay /* = 0.01f */)
{

	this->schedule(schedule_selector(BulletLayer::addBullet), delay);
}

void BulletLayer::stopShoot()
{
	this->unschedule(schedule_selector(BulletLayer::addBullet));
}

void BulletLayer::removeBullet(Sprite* bullet)
{
	if(bullet) {
		Vector<Sprite*>::iterator iter = _vAllBullet.find(bullet);
		if(iter != _vAllBullet.end()) {
			_vAllBullet.erase(iter);
			_bulletBatchNode->removeChild(bullet, true);
		}

	}
}

