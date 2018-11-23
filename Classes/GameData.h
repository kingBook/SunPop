#ifndef __GAME_DATA_H__
#define __GAME_DATA_H__
#include <iostream>
#include <vector>
using namespace std;

/*
 * 是否创建商店
 */
#ifndef GAME_IS_CREATE_SHOP
#define GAME_IS_CREATE_SHOP 0 
#endif

/*
 * 是否创建排行榜
 */
#ifndef GAME_IS_CREATE_LEADERBOARD
#define GAME_IS_CREATE_LEADERBOARD 0 
#endif

class GameData{
public:
	static int getTargetScore(int level);
	static int getShopBuyTotal(int id);//买的数量
	static int getShopGiveTotal(int id); //赠送的数量
	static float getShopMoney(int id);//需要花费的金钱
	static const bool isDebug=false;
private:
	static float _shopData[3][3];
};
#endif

/*




商城	
$0.99 	20+18 shopBtn0 com.qywl.killBlock.shopBtn0 购买钻石x20赠送x18 花费$0.99获得38颗钻石
$1.99 	50+40 shopBtn1 com.qywl.killBlock.shopBtn1 购买钻石x50赠送x40 花费$1.99获得90颗钻石
$2.99 	80+56 shopBtn2 com.qywl.killBlock.shopBtn2 购买钻石x80赠送x56 花费$2.99获得136颗钻石

///神秘大奖	------已取消
////$1.99 	50+40 bag0 com.qywl.killBlock.bag0 购买钻石x50赠送x40 花费$1.99获得90颗钻石

领取大礼包	
$0.99 	30+20 bag1 com.qywl.killBlock.bag1 购买钻石x30赠送x20 花费$0.99获得50颗钻石
*/