#include "TrademarkAnimation.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

bool TrademarkAnimation::init(){
	if(!CCLayer::init())return false;
	createBg();
	createAnimate();
	
	SimpleAudioEngine::getInstance()->playEffect("sounds/trademark.mp3");

	return true;
}

void TrademarkAnimation::createAnimate(){
    int totalFrames=319;
    SpriteFrame* frame=NULL;
    Vector<SpriteFrame*> frameVec;
    
    for(int i=1;i<=totalFrames;i++){
        
        frame=SpriteFrame::create(StringUtils::format("trademark/trademark%04d.png",i),Rect(0,0,354,270));
        frameVec.pushBack(frame);
    }
    
    Animation* animation=Animation::createWithSpriteFrames(frameVec);
    animation->setLoops(1);
    animation->setDelayPerUnit(0.04f);//: 1/帧频
    
    Animate* action=Animate::create(animation);
	
	Size size=Director::getInstance()->getVisibleSize();
	Sprite* sp=Sprite::create();
	sp->setPosition(size.width*0.5,size.height*0.5);
	this->addChild(sp);

	auto complete=[&](){
		if(_completeCallback!=nullptr)_completeCallback();
	};
	CallFunc* callFunc=CallFunc::create(complete);
	sp->runAction(Sequence::create(action,callFunc,NULL));
}

void TrademarkAnimation::createBg(){
	Sprite* bg=Sprite::create("tdbg.png");
	Size size=Director::getInstance()->getVisibleSize();
	bg->setPosition(size.width*0.5,size.height*0.5);
	this->addChild(bg);
}

void TrademarkAnimation::setCompleteCallback(const std::function<void()>& func){
	_completeCallback=func;
}

TrademarkAnimation::~TrademarkAnimation(){

}