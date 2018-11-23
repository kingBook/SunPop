#include "Star.h"
#include <iostream>
#include <string>
#include <cmath>
#include "ScoreAnim.h"
#include "GameLevel.h"
#include "MyGame.h"
#include "GameEndMessageUI.h"
#include "GameMessageUI.h"
#include "SimpleAudioEngine.h"
#include "GoodEffect.h"
#include "LocalUtil.h"
using namespace CocosDenshion;
using namespace std;

Star* Star::createEmpty(){
	Star* star=Star::create();
	star->setEmpty(true);
	return star;
}

void Star::setEmpty(bool value){_isEmpty=value;}
bool Star::IsEmpty(){return _isEmpty;}

Star::Star(){
	_moveX=UNDEFINED_VALUE;
	_moveY=UNDEFINED_VALUE;
	_isEmpty=false;
	_isStopMove=false;
	_isResumeY=false;
	_isTweenShowing=false;
	_isToTweenPosing = false;
	
}
bool Star::init(){
	if(!cocos2d::CCSprite::init())return false;
	
	return true;
}

void Star::initInstance(int color, int posId){
	_color = color;
	_posId = posId;
	string names[]={"r","g","b","v","y"};
	string fileName=names[color]+".png";
	this->initWithFile(fileName.c_str());
	scheduleUpdate();
}

void Star::changeColor(int targetColor){
	string names[]={"r","g","b","v","y"};
	string fileName=names[targetColor]+".png";
	//this->initWithFile(fileName.c_str());
	this->initWithTexture(Director::getInstance()->getTextureCache()->addImage(fileName.c_str()));
}

void Star::tweenShow(const CCPoint &offset){
	//包围星星矩阵的圆的半径
    float len = 340.0f;
	setOpacity(0);
	_initX=getPositionX();
	_initY=getPositionY();
	 //星星除去初始偏移位置后的x,y
    float x0 = _initX-offset.x-24.0f;
    float y0 = _initY-offset.y-24.0f;
	//星星矩阵的中心x,y
    float centerX = 5.0f*48.0f;
    float centerY = 5.0f*48.0f;
	//星星与中心点的夹角
    float dx = x0-centerX;
    float dy = y0-centerY;
    _angleRadian = atan2f(dy, dx);
	//从中心向外偏移
    float x1 = _initX + len * cosf(_angleRadian);
    float y1 = _initY + len * sinf(_angleRadian);
    setPosition(ccp(x1,y1));

	//将要缓的位置，比裙位置偏移一点
	float reAngleRadian = _angleRadian+M_PI;
    _tweenPos = CCPointMake(_initX+40*cosf(reAngleRadian), _initY+40*sinf(reAngleRadian));
	//计算延迟时间，离中心越远时间越长
    float d = sqrtf(dx * dx + dy * dy);
    float rate = d/400; if(rate>1)rate=1;
    float time = 1.0f*rate;
	scheduleOnce(schedule_selector(Star::setTweenShowing),time);
}

void Star::setTweenShowing(float t){
	//unschedule(schedule_selector(Star::setTweenShowing));
	_isTweenShowing = true;
	_isToTweenPosing = true;
}

void Star::addMoveDown(const CCPoint &offset){
	_posId+=1;
	int y_id = 9-(_posId&0xf);
	_moveY = 48.0f*y_id+(offset.y+24.0f);
}

void Star::addMoveLeft(int n, const CCPoint &offset){
	_posId-=(int)((1<<4)*n);
	int x_id = _posId>>4;
	_moveX = 48.0f*x_id+(offset.x+24.0f);
	//CCLOG("addMoveLeft posId:%d x_id:%d moveX:%f",_posId, x_id, _moveX);
}

void Star::update(float dt){
	if(MyGame::getInstance()->getPause())return;
	//CCLOG("%s","star update");
	if(_isTweenShowing){
		//CCLOG("%s","_isTweenShowing");
		float reAngleRadian = _angleRadian + M_PI;
		float dx = fabs(getPositionX() - _tweenPos.x);
		float dy = fabs(getPositionY() - _tweenPos.y);
		float d = sqrtf(dx * dx + dy * dy);

		float speed = 10.0f;
		if(_isToTweenPosing){
			if(d<=speed){
				setPosition(_tweenPos);
				setOpacity(255);
				_isToTweenPosing = false;
			}else{
				float vx = speed * cosf(reAngleRadian);
				float vy = speed * sinf(reAngleRadian);
				setPositionX(getPositionX()+vx);
				setPositionY(getPositionY()+vy);

				float rate = d*0.0099f;if(rate>1)rate=1;
				rate=1-rate;
				//CCLOG("d:%f, rate:%f",d,rate);
				setOpacity(255*rate);
			}
		}else{
			dx = _initX-getPositionX();
			dy = _initY-getPositionY();
			d = sqrtf(dx*dx+dy*dy);
			if(d<1){//星星缓动动画完成
				setPosition(ccp(_initX,_initY));
				_isTweenShowing = false;
			//	_game.SetStarTweenShowCount(_game.starTweenShowCount+1);
			}else{
				float vx = (_initX-getPositionX())*0.15f;
				float vy = (_initY-getPositionY())*0.15f;
				setPositionX(getPositionX()+vx);
				setPositionY(getPositionY()+vy);
			}
		}
	}else if(!_isStopMove){
		//CCLOG("%s","!isStopMove");
		 //下落移动
		if(_moveY!=UNDEFINED_VALUE){
			float dy=(float)abs((_moveY-14.0f)-getPositionY());
			if(_isResumeY){
				dy = (float)abs((_moveY-getPositionY()));
				if(dy<1){
					setPositionY(_moveY);
					_isResumeY=false;
					_moveY=UNDEFINED_VALUE;
				}else{
					float vy = (_moveY-getPositionY())*0.5f;
					setPositionY(getPositionY()+vy);
				}
			}else if(dy<3){
				setPositionY(_moveY-14.0f);//设置超出一点位置，用于缓动
			}else{
				float vy = (_moveY-0.14f - getPositionY()) * 0.3f;
				setPositionY(getPositionY()+vy);
			}
		}
		//左移
		if(_moveX!=UNDEFINED_VALUE){
			//CCLOG("%f",_moveX);
			float dx=(float)abs(_moveX-getPositionX());
			if(dx<1){
				setPositionX(_moveX);
				_moveX=UNDEFINED_VALUE;
			}else{
				float vx = (_moveX-getPositionX())*0.5f;
				setPositionX(getPositionX()+vx);
			}
		}
	}else{
		
	}
}

void Star::delayPop(float time, int score, bool isRightNowShowWardScore,int effectTypeId, bool isGameEndPop/*=false*/){
	_isDestroying=true;
	_score = score;
	_isRightNowShowWardScore=isRightNowShowWardScore;
	_effectTypeId = effectTypeId;
	_isGamendPop=isGameEndPop;
//	CCLOG("schedule 1 posId %d",_posId);
	schedule(schedule_selector(Star::popHandler),time);
}
void Star::delayPop(vector<Star*> moveStars,float time, int score, bool isRightNowShowWardScore,int effectTypeId, bool isGameEndPop/*=false*/){
	_isDestroying=true;
	_moveStars = moveStars;
	_score = score;
	_isRightNowShowWardScore=isRightNowShowWardScore;
	_effectTypeId = effectTypeId;
	_isGamendPop=isGameEndPop;
	//CCLOG("schedule 2 posId %d",_posId);
	schedule(schedule_selector(Star::popHandler),time);
}

void Star::popHandler(float t){
	unschedule(schedule_selector(Star::popHandler));
	if(!_moveStars.empty()){
		for(int i=0;i<(int)_moveStars.size();i++){
			_moveStars[i]->setIsStopMove(false);
			//CCLOG("setStopMove=false posId:%d, x_id:%d",_moveStars[i]->getPosId(),(_moveStars[i]->getPosId())>>4);
		}
		_moveStars.clear();
	}
	 //隐藏显示
	this->setVisible(false);
	//发射星星粒子
	createParticleEffect();
	//建分数动画
	if(_score>0){
		ScoreAnim* scoreAnim=ScoreAnim::create();
		scoreAnim->initInstance(_score,getPositionX(),getPositionY());
		GameLevel::getInstance()->addChild(scoreAnim);
	}
	//创建鼓励语
	if(_effectTypeId>-1)createEffect(_effectTypeId);

	if(MyGame::getInstance()->getScore() >= MyGame::getInstance()->getTargetScore()){
		MyGame::getInstance()->createMissionFinishEff();
	}

	if(_isRightNowShowWardScore){//显示奖励得分
		int rewardScore = GameEndMessageUI::getInstance()->getRewardScore();
		MyGame::getInstance()->addScore(rewardScore);
		GameMessageUI::getInstance()->updateLabelScoreText();
		GameEndMessageUI::getInstance()->moveOut();
		//检测游戏过关、失败
		MyGame::getInstance()->checkGameVictoryFailure();
	}
	if(!_isGamendPop) SimpleAudioEngine::sharedEngine()->playEffect("sounds/destroyStar.mp3");
}

void Star::createEffect(int effectTypeId){
	/*0 不错呦：6、7
      1 非常棒：8、9
      2 帅呆啦：10~
    */
	bool isCn=LocalUtil::getInstance()->getIsCn();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	const char* fileNames[3]={
		isCn?"combo_1.png":"combo_1_en.png",  
		isCn?"combo_2.png":"combo_2_en.png",  
		isCn?"combo_3.png":"combo_3_en.png"};
	GoodEffect* effect = GoodEffect::create();
	effect->initInstance(fileNames[effectTypeId]);
	effect->setPosition(ccp(visibleSize.width*0.5f,visibleSize.height*0.5f));
	StarManager::getInstance()->addChild(effect);

	const char* soundNames[3]={"sounds/combo_1.mp3","sounds/combo_2.mp3","sounds/combo_3.mp3"};
	SimpleAudioEngine::sharedEngine()->playEffect(soundNames[effectTypeId]);
}

void Star::createParticleEffect(){
	log("createParticleEffect=================");
	/*
	CCParticleExplosion* effect = CCParticleExplosion::create();
    effect->setTexture(CCTextureCache::sharedTextureCache()->addImage("star.png"));
    effect->setTotalParticles(15);
    effect->setStartColor(getColor4F(_color));
    effect->setStartColorVar(ccc4f(0,0,0,1));
    effect->setEndColor(getColor4F(_color));
    effect->setEndColorVar(ccc4f(0,0,0,1));
    effect->setStartSize(25.0f);
    effect->setGravity(Point(0,-200));
    effect->setLife(1.0f);
    effect->setSpeed(250);
    effect->setSpeedVar(20);
    effect->setPosition(getPosition());
	effect->setPosVar(Point(20,20));
	effect->setAutoRemoveOnFinish(true);
    GameLevel::getInstance()->addChild(effect);*/

	ParticleSystemQuad* effect=ParticleSystemQuad::create("effect.plist");
	effect->setTexture(Director::getInstance()->getTextureCache()->addImage("star.png"));
	effect->setStartColor(getColor4F(_color));
    effect->setStartColorVar(Color4F(0,0,0,0));
    effect->setEndColor(getColor4F(_color));
    effect->setEndColorVar(Color4F(0, 0, 0, 0));
	effect->setPosition(getPosition());
	effect->setAutoRemoveOnFinish(true);
	effect->setBlendFunc({GL_SRC_ALPHA,GL_DST_ALPHA});
	GameLevel::getInstance()->addChild(effect);
}

ccColor4F Star::getColor4F(int color){
    switch(color){
		case 0://红
			return Color4F::RED;
		case 1://绿
			return Color4F::GREEN;
		case 2://蓝
			return Color4F(0,1,1,1);
		case 3://紫
			return Color4F(1,0,1,1);
		case 4://黄
			return Color4F::YELLOW;
    }
    return ccc4f(1,1,1,0);
}

void Star::dispose(){
	_moveStars.clear();
	removeFromParentAndCleanup(true);
}

void Star::setIsStopMove(bool value){
	_isStopMove = value;
}
int Star::getPosId(){return _posId;}
int Star::getColorId(){return _color;}