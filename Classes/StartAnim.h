#ifndef __START_ANIM_H__
#define __START_ANIM_H__
#include "cocos2d.h"

class StartAnim:public cocos2d::CCLayer{
public:
	virtual bool init();
	CREATE_FUNC(StartAnim);
private:
	void createTargetScoreText();
	void createLevelText();
	void scheduleCallback(float t);
};
#endif