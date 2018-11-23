#ifndef __GAME_MESSAGE_UI_H__
#define __GAME_MESSAGE_UI_H__
#include "cocos2d.h"
USING_NS_CC;

class GameMessageUI:public cocos2d::CCLayer{
public:
	virtual bool init();
	void updateLabelLevelText();
	void updateLabelScoreText();
	float getScorePosX();
	float getScorePosY();
	static GameMessageUI* getInstance();
	~GameMessageUI();
	CREATE_FUNC(GameMessageUI);
private:
	static GameMessageUI* _instance;
	Label* _labelLevel;
	Label* _labelScore;
	void createBg();
	void createLabels();
	void pauseCallback(CCObject* pSender);
};
#endif