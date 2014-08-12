/* 游戏层
 * 包含两个元素, 1.小鸟， 2.障碍物（水管）
 * 游戏层的操作：
 * 1.游戏状态的表示
 * 2.添加小鸟和水管
 * 3.分数的实时统计
 * 4.碰撞的检测
*/

#ifndef BIRD_GAME_LAYER
#define BIRD_GAME_LAYER

#include "define.h"
#include "cocos2d.h"
#include "OptionLayer.h"
#include "BirdSprite.h"

USING_NS_CC;

NS_FLAPPYBIRD_BEGIN

const int BIRD_RADIUS = 15;

const int PIP_HEIGHT = 320;

const int PIP_WIDTH = 52;

const float PIP_SHITF_SPEED = 80.0f;

const float PIP_DISTANCE = 100;

const float PIP_COUNT = 2;

const int PIP_INTERVAL = 180;

const int WAIT_DISTANCE = 100;



const int UP_PIP = 21;
const int DOWN_PIP = 12;
const int PIP_PASS = 20;
const int PIP_NEW = 31;




typedef enum _game_status {
	GAME_STATUS_READY = 1,  // the game is not starting, just ready for player to start.
	GAME_STATUS_START,		// the game has started, and player is playing this game.
	GAME_STATUS_OVER		// the player loses this game, and the game is over.
}GameStatus;


class StatusDelegate {
public:

	virtual void onGameStart() = 0;

	// 在游戏进行中，分数改变后调用
	virtual void onGamePlaying(int score) = 0;

	virtual void onGameEnd(int curScore, int bestScore) = 0;
};

class GameLayer : public Layer , public OptionDelegate{
public:
	GameLayer() {}
	~GameLayer() {}

	virtual bool init();

	CREATE_FUNC(GameLayer);


	CC_SYNTHESIZE(StatusDelegate*, delegator, Delegator);

	void onTouch() override;

	void setPhyWorld(PhysicsWorld* world) { this->_world = world; }

	void update(float delta);

private:
	// 设置小鸟旋转， 让它看起来有重量
	void rotateBird();

	// 创建新的管道， 让它从左到右移动
	void createPips();

	int getRandomHeight();

	// 检测小鸟的碰撞
	void checkHit();


	void birdSpriteFadeOut();

	void birdSpriteRemove();

	void scrollLand(float dt);

	bool onContactBegin(/*EventCustom *event,*/ PhysicsContact& contact);

	void gameOver();

private:
	PhysicsWorld*	_world;

	GameStatus		_gameStatus;

	int				_score;

	BirdSprite*		_bird;

	Node*			_groundNode;

	std::vector<Node*>	_pips;

	Sprite*			_landSprite1;
	Sprite*			_landSprite2;

	SEL_SCHEDULE	_shiftLand;

};

NS_FLAPPYBIRD_END

#endif  // end BIRD_GAME_LAYER
