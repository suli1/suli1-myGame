/* ��Ϸ��
 * ��������Ԫ��, 1.С�� 2.�ϰ��ˮ�ܣ�
 * ��Ϸ��Ĳ�����
 * 1.��Ϸ״̬�ı�ʾ
 * 2.���С���ˮ��
 * 3.������ʵʱͳ��
 * 4.��ײ�ļ��
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

	// ����Ϸ�����У������ı�����
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
	// ����С����ת�� ����������������
	void rotateBird();

	// �����µĹܵ��� �����������ƶ�
	void createPips();

	int getRandomHeight();

	// ���С�����ײ
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
