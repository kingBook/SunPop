#ifndef __STAR_H__
#define __STAR_H__
#define UNDEFINED_VALUE 1e6f
#define STAR_TYPE "Star_Type"
#include <iostream>
#include <vector>
#include <string>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class Star:public cocos2d::CCSprite{
public:
	Star();
	static Star* createEmpty();
	void setEmpty(bool value);
	bool IsEmpty();
	virtual bool init();
	void initInstance(int color, int posId);
	void tweenShow(const CCPoint &offset);
	void addMoveDown(const CCPoint &offset);
	void addMoveLeft(int n, const CCPoint &offset);
	void delayPop(float time, int score=0, bool isRightNowShowWardScore=false,int effectTypeId=-1,bool isGameEndPop=false);
	void delayPop(vector<Star*> moveStars,float time, int score=0, bool isRightNowShowWardScore=false,int effectTypeId=-1,bool isGameEndPop=false);
	void setIsStopMove(bool value);
	void changeColor(int targetColor);
	void dispose();
	int getPosId();
	int getColorId();
	CREATE_FUNC(Star);
private:
	bool _isEmpty;
	float _angleRadian;
	float _initX;
	float _initY;
	int _color;
	int _posId;
	float _moveX;
	float _moveY;
	bool _isStopMove;
	bool _isTweenShowing;
	bool _isToTweenPosing;
	bool _isResumeY;
	bool _isDestroying;
	bool _isGamendPop;
	CCPoint _tweenPos;
	vector<Star*> _moveStars;
	int _score;
	bool _isRightNowShowWardScore;
	int _effectTypeId;
	virtual void update(float dt);
	void popHandler(float t);
	void setTweenShowing(float t);
	void createEffect(int effectTypeId);
	void createParticleEffect();
	ccColor4F getColor4F(int color);
};
#endif