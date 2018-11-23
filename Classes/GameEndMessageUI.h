#ifndef __GAME_END_MESSAGE_UI_H__
#define __GAME_END_MESSAGE_UI_H__
#include "cocos2d.h"
USING_NS_CC;

class GameEndMessageUI:public cocos2d::CCLayer{
public:
	~GameEndMessageUI();
	virtual bool init();
	static GameEndMessageUI* getInstance();
	void setRemainStars(int value);
	void setRewardScore(int value);
	void moveOut();
	int getRewardScore();
	CREATE_FUNC(GameEndMessageUI);
private:
	int _rewardScore;
	Label* _labelRewardScore;//奖励分数
	Label* _labelRemainStars;//剩下的星星
	static GameEndMessageUI* _instance;
	void updateLabelReWardScore(int value);
	void dispose(float t);
};
#endif