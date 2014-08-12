#ifndef BIRD_STATUS_LAYER
#define BIRD_STATUS_LAYER

#include "cocos2d.h"
#include "GameLayer.h"

USING_NS_CC;
using namespace std;

NS_FLAPPYBIRD_BEGIN

const string NUMBER_SCORE = "number_score";
const string NUMBER_FONT = "font";
const int CURRENT_SCORE_SPRITE_TAG = 10001;

class StatusLayer : public Layer, public StatusDelegate {
public:
	StatusLayer() {}
	~StatusLayer() {}

	virtual bool init();

	CREATE_FUNC(StatusLayer);

	void onGameStart() override;
	void onGamePlaying(int score) override;
	void onGameEnd(int curScore, int bestScore) override;

private:
	void showStartStatus();

	void showReadyStatus();

	void showOverStatus(int curScore, int bestScore);

	void loadWhiteSprite();

	void blinkFullScreen();

	void fadeInGameOver();

	void jumpToScorePanel();

	void fadeInRestartBtn();

	void refreshScoreCallback();

	void refreshScoreExecutor(float dt);

	string getMedalsName(int score);

	void setBlinkSprite();

	void blinkAction();

	void menuRestartCallback(Ref *sender);

private:
	Sprite*		_blink;
	Sprite*		_scoreSprite;
	Sprite*		_getreadySprite;
	Sprite*		_tutorialSprite;
	Sprite*		_whiteSprite;

	int			_currentScore;
	int			_bestScore;
	int			_tmpScore;

	bool		_isNewRecord;

	Point		_originPoint;

	Size		_visibleSize;
};

NS_FLAPPYBIRD_END

#endif