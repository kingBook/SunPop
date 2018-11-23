#ifndef __RECEIVE_GAG_H__
#define __RECEIVE_GAG_H__
#include "cocos2d.h"
USING_NS_CC;
/**领取大礼包*/
class ReceiveBag:public cocos2d::CCSprite{
public:
	virtual bool init();
	void setIsContinueGame(bool valeue);
	CREATE_FUNC(ReceiveBag);
private:
	bool _isContinueGame;
	void closeCallback(CCObject* pSender);
	void okCallback(CCObject* pSender);
	void payCallback(bool isFinish, int buyCount);
};
#endif