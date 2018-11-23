#ifndef __ACTIVITY_BAG_H__
#define __ACTIVITY_BAG_H__
#include "cocos2d.h"
USING_NS_CC;
/**活动大礼包*/
class ActivityBag:public cocos2d::CCSprite{
public:
	~ActivityBag();
	virtual bool init();
	CREATE_FUNC(ActivityBag);
private:
	void closeCallback(CCObject* pSender);
	void okCallback(CCObject* pSender);
	void payCallback(bool isFinish, int buyCount);
};
#endif