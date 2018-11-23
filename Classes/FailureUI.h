#ifndef __FAILURE_H__
#define __FAILURE_H__
#include "cocos2d.h"
USING_NS_CC;
class FailureUI:public cocos2d::CCSprite{
	public:
	virtual bool init();
	void setIsContinueGame(bool valeue);
	CREATE_FUNC(FailureUI);
private:
	bool _isContinueGame;
	void closeCallback(CCObject* pSender);
	void okCallback(CCObject* pSender);
};
#endif