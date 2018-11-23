#ifndef __NOVICE_BAG_H__
#define __NOVICE_BAG_H__
#include "cocos2d.h"
USING_NS_CC;
/**新手大礼包*/
class NoviceBag:public cocos2d::CCSprite{
public:
	~NoviceBag();
	virtual bool init();
	CREATE_FUNC(NoviceBag);
private:
	void closeCallback(CCObject* pSender);
	void okCallback(CCObject* pSender);
};
#endif