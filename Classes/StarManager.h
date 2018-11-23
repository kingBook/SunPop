#ifndef __STAR_MANAGER_H__
#define __STAR_MANAGER_H__
#include "cocos2d.h"
#include "StarsPosition.h"
#include "Star.h"
#include <iostream>
#include <vector>
using namespace std;
USING_NS_CC;
class StarManager:public cocos2d::CCLayer{
public:
	static StarManager* getInstance();
	~StarManager();
	virtual bool init();
	void newStarsPosition(int cnts[]);
	void pop(int posId);
	void changeOneStarColor(int curCor, int targetCor, int curPosId);
	void upset();
	//virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	void touchEndedHandler(Touch* touch, Event* event);
	bool touchBeginHandler(Touch* touch, Event* event);
	CREATE_FUNC(StarManager);
private:
	static StarManager* _instance;
	int _mvs[102];
	int _selectTotal;
	CCPoint _offset;
	std::vector<Vector<Star*>> _stars;
	StarsPosition* _starsPosition;
	void pushStar(int color,int idx,bool isTweenShow=false);
	Star* getStarAtMousePos(const CCPoint &pos);
	void checkMoveLeft(vector<Star*> &moveStars);
	void deleteOneByOne(vector<Star*> popStars, bool isAddScore=true, int scoreMul=1);
	void deleteOneByOne(vector<Star*> popStars, vector<Star*> moveStars, bool isAddScore=true, int scoreMul=1);
	void checkGameOver();
	void createChangeColorBar(Star* star);
	void popOne(int posId);
	void destroyRemainStars();
};
#endif