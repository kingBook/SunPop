#ifndef __GAME_END_ANIM_H__
#define __GAME_END_ANIM_H__
#include "cocos2d.h"
USING_NS_CC;
class GameEndAnim:public cocos2d::CCSprite{
public:
	virtual bool init();
	void initInstance(CCObject* completeTarget, SEL_CallFunc completeCallFunc);
	void animationComplete();
	CREATE_FUNC(GameEndAnim);
private:
	CCObject* _completeTarget;
	SEL_CallFunc _completeCallFunc;
};
#endif