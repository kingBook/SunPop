#ifndef __PAUSE_UI_H__
#define __PAUSE_UI_H__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class PauseUI:public cocos2d::CCSprite{
public:
	virtual bool init();
	~PauseUI();
	CREATE_FUNC(PauseUI);
private:
	void backCallback(CCObject* pSender);
	void continueCallback(CCObject* pSender);
};
#endif