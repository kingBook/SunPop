#include "GameLevel.h"
#include "MyGame.h"
#include "StartAnim.h"
#include "GameMessageUI.h"
#include "RandomArr.h"
#include "PropUI.h"
//#include "ChangeColorBar.h"

USING_NS_CC;
GameLevel* GameLevel::_instance=NULL;
bool GameLevel::init(){
	if(!CCLayer::init())return false;
	_instance=this;
	createBg();
	createGameMessageUI();
	createPropUI();
	createStartAnim();
	schedule(schedule_selector(GameLevel::createStarManager),1.5f);
	EventListenerKeyboard* listener=EventListenerKeyboard::create();
	listener->onKeyReleased=CC_CALLBACK_2(GameLevel::keyReleasedHandler,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	return true;
}

void GameLevel::createBg(){
	CCSize visibleSize=CCDirector::sharedDirector()->getVisibleSize();
	float cx = visibleSize.width*0.5f;
	float cy = visibleSize.height*0.5f;
	
	_bg = CCSprite::create("gameBg.jpg");
	_bg->setPosition(ccp(cx,cy));
	this->addChild(_bg);

}

void GameLevel::createGameMessageUI(){
	GameMessageUI* mesUI = GameMessageUI::create();
	this->addChild(mesUI);
}

void GameLevel::createPropUI(){
	PropUI* propUI = PropUI::create();
	addChild(propUI);
}

void GameLevel::createStartAnim(){
	StartAnim* startAnim = StartAnim::create();
	this->addChild(startAnim);
}

void GameLevel::createStarManager(float t){
	unschedule(schedule_selector( GameLevel::createStarManager));
	StarManager* starManager = StarManager::create();
	this->addChild(starManager);
	
	RandomArr::instance();
	int* cnts=RandomArr::randElement(100,5,12,28);//得到长度为5的数组,各个元素的和为100,元素最小12最大28如:[16, 14, 26, 24, 20 ]
	starManager->newStarsPosition(cnts);
}


void GameLevel::keyReleasedHandler(EventKeyboard::KeyCode keyCode, Event* event){
	if(GameLevel::getInstance()==NULL)return;
	if(MyGame::getInstance()->getIsGameOver())return;
	if(MyGame::getInstance()->getPause())return;
	switch(keyCode){
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			MyGame::getInstance()->createPauseUI();
			break;
		default:
			break;
	}
}

GameLevel::~GameLevel(){
	_instance=NULL;
}

GameLevel* GameLevel::getInstance(){return _instance;}