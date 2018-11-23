#ifndef __GAME_LEVEL_H__
#define __GAME_LEVEL_H__
#include "cocos2d.h"
#include "StarManager.h"
class GameLevel:public cocos2d::CCLayer{
private:
	cocos2d::CCSprite* _bg;
	StarManager* _starMan;
	void createBg();
	void createGameMessageUI();
	void createPropUI();
	void createStartAnim();
	void createStarManager(float t);
	//virtual void keyBackClicked();
	static GameLevel* _instance;
public:
	virtual bool init();
	~GameLevel();
	static GameLevel* getInstance();
	void keyReleasedHandler(EventKeyboard::KeyCode, Event*);
	CREATE_FUNC(GameLevel);
};
#endif