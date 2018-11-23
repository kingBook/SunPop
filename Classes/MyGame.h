#ifndef __MY_GAME_H__
#define __MY_GAME_H__
#include "cocos2d.h"
#include "Title.h"
#include "GameLevel.h"
#include "LocalUtil.h"
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "PluginAdMob/PluginAdMob.h"
#include "PluginIAP/PluginIAP.h"
#include "Leaderboard.h"
#endif
USING_NS_CC;

#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
class MyGame : public cocos2d::Layer, public sdkbox::IAPListener{
#else
class MyGame : public cocos2d::Layer{
#endif
private:
	static MyGame* _instance;
    std::string _bannerKey;
	std::string _fullScreenAdsKey;
	Title* _title;
	GameLevel* _gameLevel;
	bool _isMissionFinish;
    std::string _identifier;
	int _level;
	int _targetScore;
	int _score;
	int _scoreMul;
	int _maxRecord;
	int _diamondCount;
	bool _mute;
	bool _isPopOneing;
	bool _isSelectColoring;
    bool _isHasColorBar=false;
	bool _isGameOver;
	bool _pause;
    int _adsCount=0;
	int _buyCount;
	//CCObject* _payCB_this;
	//PayCB _payCB;
	bool _isCreateMysteryPrize;
	bool _isReceiveNoviceBag;//是否领取了新手礼包
	void createMysteryPrizeBag();
	void createGameLevel();
	void createFailureUI();
	void onKeyReleased(EventKeyboard::KeyCode keyCode,Event* event);
	void startDelayComplete(float t);
	void exitGame();
	void resumeAnimation(float t);
    void showBannerAd(float t);
    void hideBannerAds();
	void showFullScreenAds();
	void hideFullScreenAds();
	void initGame();
    void addAdsCount();
public:
    void setIsHasColorBar(bool value){ _isHasColorBar=value; }
    bool getIsHasColorBar(){return _isHasColorBar;}
	void showScreenMessage(const std::string &str);
	static MyGame* getInstance();
	virtual bool init();
	void createTitle(bool isClearSaveData=false, bool isDestroyLevel=false);
	void createGameEndMessageUI();
	void newGame();
	void continueGame();
	void createShop();
	void setIsPopOneing(bool value);
	void setIsSelectColoring(bool value);
	void setIsGameOver(bool value);
	bool getIsGameOver();
	bool isPopOneing();
	bool isSelectColoring();
	int getLevel();
	int getTargetScore();
	void addScore(int value);
	int getScore();
	int getMaxRecord();
	void checkGameVictoryFailure();
	void victory();
	void failure();
	void createReceiveBag(bool isContinueGame);
	void createActivityBag();
	/**创建新手礼包*/
	void createNoviceBag();
	void createGameOverAnim();
	void createWantContinueUI();
	void clearSaveData();
	void createPauseUI();
	void setIsCreateMysteryPrize(bool value);
	void setDiamondCount(int value=-1,bool isAdd=false);
	void setPause(bool pause,bool isStopOpengl=false,bool isStopSound=false);
	bool getPause();
	void setIsReceiveNoviceBaged();
	bool getIsReceiveNoviceBag();
	int getDiamondCount();
	void setMute(bool value);
	bool getMute();
	void setScoreMul(int value);
	int getScoreMul();
	void createMissionFinishEff();
	const char* getIntCString(const int n, const char* fntFile) const;
    ~MyGame();
    CREATE_FUNC(MyGame);
	//支付接口
	//void gamePay(const int money, const char* product, const char* extData,CCObject*payCB_this, PayCB cb,int buyCount);
	void payCallback(const char* result);
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
public:
	void refreshIAP(const std::string &purchaseName="");
	void purchaseIAP(const std::string &name);

	/**排行榜 用户登录*/
	void authenticateLocalUser(bool isSubmit=false,bool isShowLeaderboard=false);
	void authenticateLocalUserCallback(bool succeed);
	/**排行榜 显示排行榜*/
	void showLeaderboard();
	/**排行榜 提交分数*/
	void submitScore(int score,bool isShowLeaderboard=false);
	void submitScoreCallback(bool succeed);
private:
	//-------------------------IAP------------------------------
    virtual void onInitialized(bool ok) override;
    virtual void onSuccess(sdkbox::Product const& p) override;
    virtual void onFailure(sdkbox::Product const& p, const std::string &msg) override;
    virtual void onCanceled(sdkbox::Product const& p) override;
    virtual void onRestored(sdkbox::Product const& p) override;
    virtual void onProductRequestSuccess(std::vector<sdkbox::Product> const &products) override;
    virtual void onProductRequestFailure(const std::string &msg) override;
    void onRestoreComplete(bool ok, const std::string &msg) override;
	//----------------------------------------------
	std::string _refreshFinishPurchaseName="";
    Label* _label=NULL;
	bool _isAuthenticated=false;//是否登录了游戏中心
	bool _submitIsShow=false;
	bool _authenticatedIsSubmit=false;
	bool _authenticatedIsShow=false;
	bool _isRefreshIAP=false;
	void print(const std::string& text);
#endif /**CC_PLATFORM_IOS*/
	
};
#endif