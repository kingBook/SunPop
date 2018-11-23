#include "ScoreAnim.h"
#include "GameMessageUI.h"
#include "MyGame.h"

bool ScoreAnim::init(){
	if(!CCSprite::init())return false;

	return true;
}

void ScoreAnim::initInstance(int score,float initX,float initY){
	_score=score;
	//CCLOG("%s %d %f %f","initInstance", score,initX,initY);
	std::string scoreStr=Value(score).asString();
	Label*label=Label::create(scoreStr,"fonts/jianzhi.ttf",40);
	label->setScale(0.7f);
	addChild(label);
	//
	setPositionX(initX);
	setPositionY(initY);
	//
	float targetPosX = GameMessageUI::getInstance()->getScorePosX();
	float targetPosY = GameMessageUI::getInstance()->getScorePosY();
	float time=0.5f;
	CCMoveTo* moveTo = CCMoveTo::create(time,ccp(targetPosX,targetPosY));
	runAction(moveTo);
	scheduleOnce(schedule_selector(ScoreAnim::moveComplete),time);
}

void ScoreAnim::moveComplete(float t){
	MyGame::getInstance()->addScore(_score);
	GameMessageUI::getInstance()->updateLabelScoreText();
	removeFromParentAndCleanup(true);
}