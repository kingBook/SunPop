#ifndef __WANT_CONTINUE_UI_H__
#define  __WANT_CONTINUE_UI_H__
#include "cocos2d.h"
USING_NS_CC;
class WantContinueUI:public cocos2d::CCSprite{
public:
	virtual bool init();
	CREATE_FUNC(WantContinueUI);
private:
	void closeCallback(CCObject* pSender);
	void okCallback(CCObject* pSender);
	void payCallback(bool isFinish, int buyCount);
};
#endif