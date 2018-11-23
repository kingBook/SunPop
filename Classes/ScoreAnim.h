#ifndef __SCORE_ANIM_H__
#define __SCORE_ANIM_H__
#include "cocos2d.h"
USING_NS_CC;
class ScoreAnim:public cocos2d::CCSprite{
public:
	virtual bool init();
	void initInstance(int score,float initX,float initY);
	CREATE_FUNC(ScoreAnim);
private:
	int _score;
	void moveComplete(float t);
};
#endif