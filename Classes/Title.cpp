#include "Title.h"
#include "MyGame.h"
#include "HelpUI.h"
#include "LocalUtil.h"
#include "GameData.h"

Title* Title::_instance = NULL;
bool Title::init(){
	if(!CCLayer::init())return false;
	_instance=this;
	_enabled=true;
	_shopOnceItem=NULL;
	createBg();
	createMenuItem();
	return true;
}

void Title::createBg(){
	bool isCn=LocalUtil::getInstance()->getIsCn();
	bool isTaiwanCn=LocalUtil::getInstance()->getIsTaiwanCn();

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite* bg = CCSprite::create("title_bg.jpg");
	bg->setPosition(ccp(visibleSize.width*0.5,visibleSize.height*0.5f));
	this->addChild(bg);

	Sprite* title=Sprite::create(isCn?(isTaiwanCn?"title_taiwancn.png":"title_cn.png"):"title_en.png");
	title->setPosition(250,510);
	this->addChild(title);
}

void Title::createMenuItem(){
	//获取中心位置
	bool isCn=LocalUtil::getInstance()->getIsCn();
	bool isTaiwanCn=LocalUtil::getInstance()->getIsTaiwanCn();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	float cx = visibleSize.width*0.5f;
	float cy = visibleSize.height*0.5f;
	//
	TTFConfig ttfConfig;
	ttfConfig.fontFilePath=isCn?(isTaiwanCn?"fonts/liushu_taiwancn.ttf":"fonts/liushu.ttf"):"fonts/yaya.ttf";
	ttfConfig.outlineSize=1;
	ttfConfig.fontSize=isCn?36:30;
	//
	Vector<MenuItem*> menuItems;
#if GAME_IS_CREATE_SHOP
	//创建新手礼包按钮
	if(!MyGame::getInstance()->getIsReceiveNoviceBag()){
		std::string str_so=isCn?"Shop_Onece.png":"Shop_Onece_en.png";
		_shopOnceItem = CCMenuItemImage::create(str_so,str_so,this,menu_selector(Title::shopOnceCallback));
		_shopOnceItem->setPosition(ccp(420,330));
		CCScaleTo* scaleTo_a = CCScaleTo::create(0.5f,0.8f,0.8f);
		CCScaleTo* scaleTo_b = CCScaleTo::create(0.5f,1.0f,1.0f);
		CCSequence* sequence = CCSequence::create(scaleTo_a,scaleTo_b,NULL);
		CCRepeatForever* repeatAcion = CCRepeatForever::create(sequence);
		_shopOnceItem->runAction(repeatAcion);
		menuItems.pushBack(_shopOnceItem);
	}
#endif /*end GAME_IS_CREATE_SHOP*/
	//帮助按钮
	CCMenuItemImage* helpItem = CCMenuItemImage::create("startUI_help.png","startUI_help.png",this,menu_selector(Title::helpCallback));
	helpItem->setPosition(ccp(60,240));
	menuItems.pushBack(helpItem);
	//静音按钮
	CCMenuItemImage* mute1Item = CCMenuItemImage::create("mute0001.png","mute0001.png",this,menu_selector(Title::muteCallback));
	mute1Item->setTag(1);
	CCMenuItemImage* mute2Item = CCMenuItemImage::create("mute0002.png","mute0002.png",this,menu_selector(Title::muteCallback));
	mute2Item->setTag(2);
	bool curMute = MyGame::getInstance()->getMute();
	CCMenuItemToggle* muteItem =CCMenuItemToggle::createWithTarget(this,menu_selector(Title::muteCallback),curMute?mute2Item:mute1Item,curMute?mute1Item:mute2Item,NULL);
	muteItem->setPosition(ccp(60,320));
	menuItems.pushBack(muteItem);
	
#if GAME_IS_CREATE_LEADERBOARD
	float dy=70;
	float startBtnY=cy-70;
#else
	float dy=100;
	float startBtnY=cy-90;
#endif/*end GAME_IS_CREATE_LEADERBOARD*/

	//创建开始按钮
	CCMenuItemImage* startItem = CCMenuItemImage::create("menu_start.png","menu_start.png",this,menu_selector(Title::startCallback));
	startItem->setPosition(ccp(-startItem->getContentSize().width*0.5f,startBtnY));
	CCMoveTo* moveTo = CCMoveTo::create(0.4f,ccp(cx,startBtnY));
	startItem->runAction(moveTo);

	Label*startLabel=Label::createWithTTF(ttfConfig,LocalUtil::getInstance()->getKeyString("newGame"),TextHAlignment::CENTER);
	startLabel->setPosition(Vec2(startItem->getContentSize().width*0.5f,startItem->getContentSize().height*0.6f));
	startItem->addChild(startLabel); 
	//创建继续游戏按钮
	CCMenuItemImage* continueItem = CCMenuItemImage::create("menu_continue.png","menu_continue.png",this,menu_selector(Title::continueCallback));
	continueItem->setPosition(ccp(visibleSize.width+continueItem->getContentSize().width*0.5f,startItem->getPosition().y-dy));
	moveTo = CCMoveTo::create(0.4f,ccp(cx,startItem->getPosition().y-dy));
	continueItem->runAction(moveTo);

	Label*continueLabel=Label::createWithTTF(ttfConfig,LocalUtil::getInstance()->getKeyString("continueGame"),TextHAlignment::CENTER);
	continueLabel->setPosition(Vec2(continueItem->getContentSize().width*0.5f,continueItem->getContentSize().height*0.6f));
	continueItem->addChild(continueLabel);

#if GAME_IS_CREATE_SHOP
	//创建商城按钮
	CCMenuItemImage* shopItem = CCMenuItemImage::create("menu_shop.png","menu_shop.png",this,menu_selector(Title::shopCallback));
	shopItem->setPosition(ccp(-shopItem->getContentSize().width*0.5f,continueItem->getPosition().y-dy));
	moveTo = CCMoveTo::create(0.4f,ccp(cx,continueItem->getPosition().y-dy));
	shopItem->runAction(moveTo);
	Label*shopLabel=Label::createWithTTF(ttfConfig,LocalUtil::getInstance()->getKeyString("shop"),TextHAlignment::CENTER);
	shopLabel->setPosition(Vec2(shopItem->getContentSize().width*0.5f,shopItem->getContentSize().height*0.6f));
	shopItem->addChild(shopLabel);
#endif/*end GAME_IS_CREATE_SHOP*/

#if GAME_IS_CREATE_LEADERBOARD
	//创建排行榜按钮
	CCMenuItemImage* leaderboardItem = CCMenuItemImage::create("menu_start.png","menu_start.png",this,menu_selector(Title::leaderboardCallback));
#if GAME_IS_CREATE_SHOP
	leaderboardItem->setPosition(ccp(-shopItem->getContentSize().width*0.5f,shopItem->getPosition().y-dy));
	moveTo = CCMoveTo::create(0.4f,ccp(cx,shopItem->getPosition().y-dy));
#else
	leaderboardItem->setPosition(ccp(-continueItem->getContentSize().width*0.5f,continueItem->getPosition().y-dy));
	moveTo = CCMoveTo::create(0.4f,ccp(cx,continueItem->getPosition().y-dy));
#endif/*end GAME_IS_CREATE_SHOP*/
	leaderboardItem->runAction(moveTo);
	Label*leaderboardLabel=Label::createWithTTF(ttfConfig,LocalUtil::getInstance()->getKeyString("leaderboard"),TextHAlignment::CENTER);
	leaderboardLabel->setPosition(Vec2(leaderboardItem->getContentSize().width*0.5f,leaderboardItem->getContentSize().height*0.6f));
	leaderboardItem->addChild(leaderboardLabel);
#endif/*end GAME_IS_CREATE_LEADERBOARD*/
	//
	menuItems.pushBack(startItem);
	menuItems.pushBack(continueItem);
#if GAME_IS_CREATE_SHOP
	menuItems.pushBack(shopItem);
#endif/*end GAME_IS_CREATE_SHOP*/
#if GAME_IS_CREATE_LEADERBOARD
	menuItems.pushBack(leaderboardItem);
#endif/*end GAME_IS_CREATE_LEADERBOARD*/
	//添加到菜单
	CCMenu* menu=CCMenu::createWithArray(menuItems);
	menu->setPosition(Point(0,0));
	this->addChild(menu);
}

void Title::startCallback(CCObject* pSender){
	if(!_enabled)return;
	removeFromParentAndCleanup(true);
	MyGame::getInstance()->newGame();
}

void Title::continueCallback(CCObject* pSender){
	if(!_enabled)return;
	removeFromParentAndCleanup(true);
	MyGame::getInstance()->continueGame();
}

void Title::shopCallback(CCObject* pSender){
	if(!_enabled)return;
	MyGame::getInstance()->createShop();
}

void Title::shopOnceCallback(CCObject* pSender){
	if(!_enabled)return;
	MyGame::getInstance()->createNoviceBag();
}

void Title::leaderboardCallback(CCObject* pSender){
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	MyGame::getInstance()->showLeaderboard();
#endif
}
void Title::helpCallback(CCObject* pSender){
	int tag = 101;
	if(getChildByTag(101)!=NULL)return;
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	HelpUI* helpUI = HelpUI::create();
	helpUI->setPosition(ccp(visibleSize.width*0.5f,visibleSize.height*0.5f));
	helpUI->setTag(101);
	addChild(helpUI);
}

void Title::muteCallback(CCObject* pSender){
	bool curMute = MyGame::getInstance()->getMute();
	MyGame::getInstance()->setMute(!curMute);
}

void Title::setEnabled(bool value){
	if(this==nullptr)return;
	_enabled = value;
}

void Title::hideShopOnceItem(){
	if(_shopOnceItem!=NULL){
		_shopOnceItem->setVisible(false);
	}
}

Title::~Title(){
	_instance=NULL;
	_shopOnceItem=NULL;
}

Title* Title::getInstance(){return _instance;}