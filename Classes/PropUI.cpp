#include "PropUI.h"
#include "MyGame.h"
#include "SimpleAudioEngine.h"
#include "ScreenText.h"
#include "LocalUtil.h"
#include "GameData.h"
using namespace CocosDenshion;

bool PropUI::init(){
	if(!CCLayer::init())return false;
	_instance = this;
	_enabled = true;
	createMenuItem();
	setPositionX(boundingBox().size.width);
	//添加滑入动作
	CCMoveTo* moveTo = CCMoveTo::create(1,Point());
	CCSequence* seq = CCSequence::create(CCDelayTime::create(1.5f),moveTo,NULL);
	runAction(seq);
	setTouchEnabled(true);
	return true;
}

void PropUI::createMenuItem(){
# if GAME_IS_CREATE_SHOP
	CCSprite* bottom = CCSprite::create("bottom0.png");
	bottom->setPosition(ccp(390,665));
	addChild(bottom);
	CCSprite* zuanshi = CCSprite::create("zuanshi.png");
	zuanshi->setPosition(ccp(335,668));
	zuanshi->setScale(0.8f);
	addChild(zuanshi);
	CCSprite* btn_addDiamond = CCSprite::create("btn_add.png");
	btn_addDiamond->setPosition(ccp(450,665));
	addChild(btn_addDiamond);

	//颗数
	std::string count=Value(MyGame::getInstance()->getDiamondCount()).asString();
	_diamondCountText=Label::create(count,"fonts/jianzhi.ttf",40);
	_diamondCountText->setScale(0.6f);
	_diamondCountText->setPosition(ccp(390,665));
	_diamondCountText->setColor(ccc3(189,15,0));
	addChild(_diamondCountText);

	CCMenuItemImage* addDiamondItem=CCMenuItemImage::create("btnAddRect.png","btnAddRect.png",this,menu_selector(PropUI::addDiamondCallback));
	addDiamondItem->setOpacity(0);
	addDiamondItem->setPosition(ccp(390,665));
#endif/*end GAME_IS_CREATE_SHOP*/

	//add props button----------------------------------------------
	CCPoint pos0 = ccp(275,610);
	float interval = 58;
	CCMenuItemImage* ranItem = CCMenuItemImage::create("prop_random.png","prop_random.png",this,menu_selector(PropUI::randCallback));
	ranItem->setPosition(pos0);
	CCMenuItemImage* selectColorItem = CCMenuItemImage::create("prop_selectColor.png","prop_selectColor.png",this,menu_selector(PropUI::selectColorCallback));
	selectColorItem->setPosition(pos0+ccp(interval,0));
	CCMenuItemImage* coinAddItem = CCMenuItemImage::create("prop_coinAdd.png","prop_coinAdd.png",this,menu_selector(PropUI::coinAddCallback));
	coinAddItem->setPosition(pos0+ccp(interval*2,0));
	CCMenuItemImage* popOneItem = CCMenuItemImage::create("prop_popOne.png","prop_popOne.png",this,menu_selector(PropUI::popOneCallback));
	popOneItem->setPosition(pos0+ccp(interval*3,0));
# if GAME_IS_CREATE_SHOP
	_menu=CCMenu::create(addDiamondItem,ranItem,selectColorItem,coinAddItem,popOneItem,NULL);
#else
	_menu=CCMenu::create(ranItem,selectColorItem,coinAddItem,popOneItem,NULL);
#endif/*end GAME_IS_CREATE_SHOP*/
	_menu->setPosition(Point());
	addChild(_menu);
}

void PropUI::updateDiamondText(){
# if GAME_IS_CREATE_SHOP
	std::string count=Value(MyGame::getInstance()->getDiamondCount()).asString();
	_diamondCountText->setString(count);
#endif/*end GAME_IS_CREATE_SHOP*/
}

void PropUI::randCallback(CCObject* pSender){
	if(!_enabled)return;
	if(MyGame::getInstance()->getPause())return;
# if GAME_IS_CREATE_SHOP
	if(MyGame::getInstance()->getDiamondCount()<5){
		MyGame::getInstance()->setPause(true);
		MyGame::getInstance()->createReceiveBag(false);
		return;
	}
	MyGame::getInstance()->setDiamondCount(MyGame::getInstance()->getDiamondCount()-5);
#endif/*end GAME_IS_CREATE_SHOP*/
	StarManager::getInstance()->upset();
	playerClickSound();
	SimpleAudioEngine::sharedEngine()->playEffect("sounds/Props_random.ogg");
	createScreenText("screenTextPropRandom");
}

void PropUI::selectColorCallback(CCObject* pSender){
	if(!_enabled)return;
	if(MyGame::getInstance()->getPause())return;
# if GAME_IS_CREATE_SHOP
	if(MyGame::getInstance()->getDiamondCount()<5){
		MyGame::getInstance()->setPause(true);
		MyGame::getInstance()->createReceiveBag(false);
		return;
	}
	MyGame::getInstance()->setDiamondCount(MyGame::getInstance()->getDiamondCount()-5);
#endif/*end GAME_IS_CREATE_SHOP*/
	MyGame::getInstance()->setIsSelectColoring(true);
	playerClickSound();
	setEnabled(false);
	createScreenText("screenTextPropChangeColor");
}

void PropUI::coinAddCallback(CCObject* pSender){
	if(!_enabled)return;
	if(MyGame::getInstance()->getPause())return;
# if GAME_IS_CREATE_SHOP
	if(MyGame::getInstance()->getDiamondCount()<5){
		MyGame::getInstance()->setPause(true);
		MyGame::getInstance()->createReceiveBag(false);
		return;
	}
	MyGame::getInstance()->setDiamondCount(MyGame::getInstance()->getDiamondCount()-5);
#endif/*end GAME_IS_CREATE_SHOP*/
	MyGame::getInstance()->setScoreMul(2);
	playerClickSound();
	createScreenText("screenTextPropScoreMul");
}

void PropUI::popOneCallback(CCObject* pSender){
	if(!_enabled)return;
	if(MyGame::getInstance()->getPause())return;
# if GAME_IS_CREATE_SHOP
	if(MyGame::getInstance()->getDiamondCount()<5){
		MyGame::getInstance()->setPause(true);
		MyGame::getInstance()->createReceiveBag(false);
		return;
	}
	MyGame::getInstance()->setDiamondCount(MyGame::getInstance()->getDiamondCount()-5);
#endif/*end GAME_IS_CREATE_SHOP*/
	playerClickSound();
	MyGame::getInstance()->setIsPopOneing(true);
	setEnabled(false);
	createScreenText("screenTextPropPopOne");
}

void PropUI::setEnabled(bool value){
	_enabled = value;
	setTouchEnabled(value);
	if(_enabled){
		_menu->setOpacity(255);
	}else{
		_menu->setOpacity(125);
	}
}

void PropUI::createScreenText(const char* stringKey){
	//bool isCn=LocalUtil::getInstance()->getIsCn();
	//bool isTaiwanCn=LocalUtil::getInstance()->getIsTaiwanCn();
	std::string str=LocalUtil::getInstance()->getKeyString(stringKey,true);

	ScreenText* screenText = ScreenText::create();
	screenText->initInstance(str.c_str());
	GameLevel::getInstance()->addChild(screenText);
}

void PropUI::addDiamondCallback(CCObject* pSender){
	if(!_enabled)return;
	if(MyGame::getInstance()->getPause())return;
	MyGame::getInstance()->setPause(true);
	MyGame::getInstance()->createReceiveBag(false);
}

void PropUI::playerClickSound(){
	SimpleAudioEngine::sharedEngine()->playEffect("sounds/coin.ogg");
}

PropUI* PropUI::_instance=NULL;
PropUI* PropUI::getInstance(){
	return _instance;
}

PropUI::~PropUI(){
	_diamondCountText=NULL;
	_instance=NULL;
}