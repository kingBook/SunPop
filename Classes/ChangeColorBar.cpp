#include "ChangeColorBar.h"
#include "StarManager.h"
#include "PropUI.h"
#include "SimpleAudioEngine.h"
#include "MyGame.h"
using namespace CocosDenshion;

void ChangeColorBar::initInstance(int curColor, int curPosId){
	_curColor=curColor;
	_curPosId=curPosId;
}

bool ChangeColorBar::init(){
	if(!CCLayer::init())return false;
    MyGame::getInstance()->setIsHasColorBar(true);
	return true;
}

void ChangeColorBar::onEnter(){
	createBgRect();
	createPaintArrow();
	createMenuItems();

	CCLayer::onEnter();/********漏写将不触发菜单点击****/
}

void ChangeColorBar::createPaintArrow(){
	_paintArrow = CCSprite::create("paint_arrow.png");
	_paintArrow->setPosition(ccp(3,5));
	addChild(_paintArrow);
}

void ChangeColorBar::createBgRect(){
	_bgRect = CCSprite::create("paint_bg.png");
	_bgRect->setScaleX(0.9f);
	_bgRect->setPosition(ccp(0,48));
	//限制边界
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCRect bound = _bgRect->boundingBox();
	float minX = getPositionX()-bound.size.width*0.5f;
	float maxX = getPositionX()+bound.size.width*0.5f;
	//CCLOG("%f,%f,%f,%f,%f",bound.getMinX(),bound.getMaxX(),bound.size.width,bound.size.height,getPositionX());
	if(minX<0)						_bgRect->setPositionX(105);
	else if(maxX>visibleSize.width) _bgRect->setPositionX(-105);
	//
	addChild(_bgRect);
}

void ChangeColorBar::createMenuItems(){
	float scale=1;
	float w=48*scale;
	float y=2;
	CCMenuItemImage* r_item=CCMenuItemImage::create("r.png","r.png",this,menu_selector(ChangeColorBar::r_menuCallback));
	r_item->setScale(scale);
	r_item->setPosition(ccp(-w*2,y));
	CCMenuItemImage* g_item=CCMenuItemImage::create("g.png","g.png",this,menu_selector(ChangeColorBar::g_menuCallback));
	g_item->setScale(scale);
	g_item->setPosition(ccp(-w,y));
	CCMenuItemImage* b_item=CCMenuItemImage::create("b.png","b.png",this,menu_selector(ChangeColorBar::b_menuCallback));
	b_item->setScale(scale);
	b_item->setPosition(ccp(0,y));
	CCMenuItemImage* v_item=CCMenuItemImage::create("v.png","v.png",this,menu_selector(ChangeColorBar::v_menuCallback));
	v_item->setScale(scale);
	v_item->setPosition(ccp(w,y));
	CCMenuItemImage* y_item=CCMenuItemImage::create("y.png","y.png",this,menu_selector(ChangeColorBar::y_menuCallback));
	y_item->setScale(scale);
	y_item->setPosition(ccp(w*2,y));
	CCMenu* _menu = CCMenu::create(r_item,g_item,b_item,v_item,y_item,NULL);
	_menu->setPosition(_bgRect->getPosition());
	addChild(_menu);
}

void ChangeColorBar::r_menuCallback(CCObject* pSender){
	StarManager::getInstance()->changeOneStarColor(_curColor,0,_curPosId);
	removeFromParentAndCleanup(true);
	playSelectSound();
}

void ChangeColorBar::g_menuCallback(CCObject* pSender){
	StarManager::getInstance()->changeOneStarColor(_curColor,1,_curPosId);
	removeFromParentAndCleanup(true);
	playSelectSound();
}

void ChangeColorBar::b_menuCallback(CCObject* pSender){
	StarManager::getInstance()->changeOneStarColor(_curColor,2,_curPosId);
	removeFromParentAndCleanup(true);
	playSelectSound();
}

void ChangeColorBar::v_menuCallback(CCObject* pSender){
	StarManager::getInstance()->changeOneStarColor(_curColor,3,_curPosId);
	removeFromParentAndCleanup(true);
	playSelectSound();
}

void ChangeColorBar::y_menuCallback(CCObject* pSender){
	StarManager::getInstance()->changeOneStarColor(_curColor,4,_curPosId);
	removeFromParentAndCleanup(true);
	playSelectSound();
}

ChangeColorBar::~ChangeColorBar(){
    MyGame::getInstance()->setIsHasColorBar(false);
	_paintArrow=NULL;
	_bgRect=NULL;
}

void ChangeColorBar::playSelectSound(){
	SimpleAudioEngine::sharedEngine()->playEffect("sounds/Props_changeColor.ogg");
}