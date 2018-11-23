#include "Shop.h"
#include "GameData.h"
#include "Title.h"
#include "MyGame.h"
#include "LocalUtil.h"

bool Shop::init(){
	if(!CCSprite::init())return false;
	bool isCn=LocalUtil::getInstance()->getIsCn();
	bool isTaiwanCn=LocalUtil::getInstance()->getIsTaiwanCn();
	_instance=this;
	Title::getInstance()->setEnabled(false);//禁点标题
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//创建背景
	CCLayerColor* bgColor = CCLayerColor::create(ccc4(0,0,0,125));
	bgColor->setPosition(ccp(-visibleSize.width*0.5f,-visibleSize.height*0.5f));
	addChild(bgColor);
	
	CCSprite* bg = CCSprite::create("shopBg.png");
	TTFConfig ttfConfig;
	ttfConfig.fontFilePath=isTaiwanCn?"fonts/haibao_taiwancn.ttf":"fonts/haibao.ttf";
	ttfConfig.fontSize=60;
	std::string strTitle=LocalUtil::getInstance()->getKeyString("shop",true);
	Label*bgTitleLabel=Label::createWithTTF(ttfConfig,strTitle);
	bgTitleLabel->enableOutline(Color4B(0,100,0,255),2);
	bgTitleLabel->enableShadow(Color4B(0,30,0,255));
	bgTitleLabel->setHorizontalAlignment(TextHAlignment::CENTER);
	bgTitleLabel->setVerticalAlignment(TextVAlignment::CENTER);
	bgTitleLabel->setPosition(240,650);
	bg->addChild(bgTitleLabel);

	addChild(bg);

	//你拥有钻石   颗
	std::string str_yh=LocalUtil::getInstance()->getKeyString("niyongyouzuanshi");
	std::string str_count=isCn?"                 ":"          ";
	std::string str_ke=LocalUtil::getInstance()->getKeyString("ke");
	std::string str=str_yh+str_count+str_ke;
	std::string fontFile=isCn?"fonts/jianzhi.ttf":"fonts/haibao.ttf";
	Label*label_yh=Label::createWithTTF(str,fontFile,25);
	label_yh->setPosition(Vec2(0,160));
	label_yh->setTextColor(Color4B(64,32,0,255));
	addChild(label_yh);

	updateDiamondText();

	Vector<MenuItem*>menuItems;
	float y0 = -150;
	float d = 110;
	for(int i=0; i<3; i++){
		CCSprite* btnBg = CCSprite::create("shopBtnBg.png");
		btnBg->setPositionY(y0+d*i);
		addChild(btnBg);

		CCSprite* zuanshi_a = CCSprite::create("zuanshi.png");
		zuanshi_a->setPosition(ccp(-145,y0+d*i));
		addChild(zuanshi_a);

		//购买的数量
		std::string str="x";
		str+=Value(GameData::getShopBuyTotal(i)).asString();
		Label*label_x0=Label::createWithTTF(str,"fonts/haibao.ttf",20);
		label_x0->setPosition(Vec2(-100,-165+d*i));
		addChild(label_x0);

		CCSprite* zuanshi_b = CCSprite::create("zuanshi.png");
		zuanshi_b->setScale(0.8f);
		zuanshi_b->setPosition(ccp(10,-155+d*i));
		addChild(zuanshi_b);

		//赠送的数量
		str="x";
		str+=Value(GameData::getShopGiveTotal(i)).asString();
		Label*label_x1=Label::createWithTTF(str,"fonts/haibao.ttf",20);
		label_x1->setPosition(Vec2(50,-165+d*i));
		addChild(label_x1);

		CCSprite* zeng = CCSprite::create(isCn?"zeng.png":"zeng_en.png");
		zeng->setPosition(ccp(-50,-140+d*i));
		addChild(zeng);

		CCSprite* buyBtn=CCSprite::create("buy.png");
		buyBtn->setPosition(ccp(125,y0+d*i));
		addChild(buyBtn);

		str=Value(GameData::getShopMoney(i)).asString();
		str=str.substr(0,4);
		Label*label_money=Label::createWithTTF(str,"fonts/haibao.ttf",15);
		label_money->setTextColor(Color4B(255,50,0,255));
		label_money->setPosition(Vec2(130,y0+d*i+3));
		addChild(label_money);
		if(i==0){
			CCSprite* zuiHuaSuan=CCSprite::create(isCn?(isTaiwanCn?"zuiHuaSuan_taiwancn.png":"zuiHuaSuan.png"):"zuiHuaSuan_en.png");
			zuiHuaSuan->setPosition(ccp(155,y0+d*i+36));
			addChild(zuiHuaSuan);
		}else if(i==1){
			CCSprite* reixiao=CCSprite::create(isCn?"reixiao.png":"reixiao_en.png");
			reixiao->setPosition(ccp(155,y0+d*i+36));
			addChild(reixiao);
		}

		CCMenuItemImage* rect_cItem = CCMenuItemImage::create("rect_c.png","rect_c.png",this,menu_selector(Shop::buyCallback));
		rect_cItem->setOpacity(0);
		rect_cItem->setTag(i);
		rect_cItem->setPosition(ccp(125,y0+d*i));
		menuItems.pushBack(rect_cItem);
	}

	CCMenuItemImage* closeItem = CCMenuItemImage::create("close.png","close.png",this,menu_selector(Shop::closeCallback));
	closeItem->setPosition(ccp(-170,241));
	menuItems.pushBack(closeItem);

	CCMenu* menu =CCMenu::createWithArray(menuItems);
	menu->setPosition(Point());
	addChild(menu);
	//放大出现
	setScale(0.1f);
	CCScaleTo* scaleTo = CCScaleTo::create(0.5f,1.0f,1.0f);
	runAction(scaleTo);
	return true;
}

void Shop::updateDiamondText(){
	bool isCn=LocalUtil::getInstance()->getIsCn();
	std::string str=Value(MyGame::getInstance()->getDiamondCount()).asString();
	if(_diamondCountLabel==nullptr){
		Label*_diamondCountLabel=Label::createWithTTF(str,"fonts/jianzhi.ttf",25);
		_diamondCountLabel->setHorizontalAlignment(TextHAlignment::CENTER);
		_diamondCountLabel->setPosition(Vec2(isCn?50:0,160));
		_diamondCountLabel->setTextColor(Color4B(200,0,0,255));
		addChild(_diamondCountLabel);
	}else{
		_diamondCountLabel->setString(str);
	}
}

void Shop::closeCallback(CCObject* pSender){
	CCLOG("%s","Shop::closeCallback();");
	removeAllChildrenWithCleanup(true);
	removeFromParentAndCleanup(true);
	Title::getInstance()->setEnabled(true);
}

void Shop::buyCallback(CCObject* pSender){
	CCLOG("%s","Shop::buyCallback();");
	CCMenuItemImage* rect_cItem = (CCMenuItemImage*)pSender;
	int tag = rect_cItem->getTag();
	CCLOG("%d",tag);
	float moneys[3]={2.99f,1.99f,0.99f};
	int totals[3] = {80+56, 50+40, 20+18};
	const char* products[3] = {
		"shopBtn2",
		"shopBtn1",
		"shopBtn0"};
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	MyGame::getInstance()->purchaseIAP(products[tag]);
#endif
	//MyGame::getInstance()->gamePay(moneys[tag],products[tag],"",this,pay_cb(Shop::payCallback),totals[tag]);
}


void Shop::payCallback(bool isFinish, int buyCount){
	CCLOG("shop::payCallback():%s, %d",isFinish?"ok":"no", buyCount);
	if(isFinish){
		MyGame::getInstance()->setDiamondCount(buyCount,true);
		updateDiamondText();
	}
}

Shop::~Shop(){
	_instance=NULL;
}

Shop* Shop::_instance=NULL;
Shop* Shop::getInstance(){
	return _instance;
}