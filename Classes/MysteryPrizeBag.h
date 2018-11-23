#ifndef __MY_STERY_PRIZE_BAG_H__
#define __MY_STERY_PRIZE_BAG_H__
#include "cocos2d.h"
USING_NS_CC;

class MysteryPrizeBag:public cocos2d::CCSprite{
public:
	~MysteryPrizeBag();
	virtual bool init();
	CREATE_FUNC(MysteryPrizeBag);
private:
	void closeCallback(CCObject* pSender);
	void okCallback(CCObject* pSender);
	void payCallback(bool isFinish, int buyCount);
};
#endif